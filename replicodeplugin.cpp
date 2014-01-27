#include "replicodeplugin.h"
#include "replicodeconfigpage.h"
#include "replicodesettings.h"

#include <QtGlobal>
#include <QProcess>
#include <QTemporaryFile>

#include <KPluginFactory>
#include <KPluginLoader>
#include <KLocale>
#include <KAction>
#include <KActionCollection>
#include <KAboutData>
#include <kate/application.h>
#include <QDebug>
#include <qfileinfo.h>
#include <kate/mainwindow.h>
#include <QMessageBox>
#include <KGlobal>
#include <KConfigGroup>
#include <KTextEditor/View>
#include <KTextEditor/Document>
#include <QListWidget>
#include <QVBoxLayout>
#include <QProcess>

K_PLUGIN_FACTORY(KateReplicodeFactory, registerPlugin<ReplicodePlugin>();)
//K_EXPORT_PLUGIN(KateReplicodeFactory(KAboutData("katereplicode","katereplicodeplugin",ki18n("Replicode"), "0.1", ki18n("Replicode Integration"), KAboutData::License_LGPL_V2)) )
K_EXPORT_PLUGIN(KateReplicodeFactory("katereplicodeplugin"))

ReplicodePlugin::ReplicodePlugin(QObject* parent, const QList< QVariant > &args)
: Kate::Plugin(qobject_cast<Kate::Application*>(parent))
{
}

ReplicodePlugin::~ReplicodePlugin()
{
}
uint ReplicodePlugin::configPages() const
{
    return 1;
}

QString ReplicodePlugin::configPageFullName(uint number) const
{
    Q_ASSERT(number == 0);
    return i18n("Replicode settings");
}

QString ReplicodePlugin::configPageName(uint number) const
{
    Q_ASSERT(number == 0);
    return i18n("Replicode");
}


KIcon ReplicodePlugin::configPageIcon(uint number) const
{
    return KIcon("code-block");
}

Kate::PluginConfigPage* ReplicodePlugin::configPage(uint number, QWidget* parent, const char* name)
{
    Q_UNUSED(name);
    Q_ASSERT(number == 0);
    return new ReplicodeConfigPage(parent, name);
}

ReplicodeView::ReplicodeView(Kate::MainWindow* mainWindow)
: Kate::PluginView(mainWindow), Kate::XMLGUIClient(KateReplicodeFactory::componentData()), m_mainWindow(mainWindow), m_settingsFile(0), m_executor(0)
{
    KAction *action = new KAction(KIcon("code-block"), i18n("Run replicode"), this);
    action->setShortcut(Qt::Key_F8);
    connect(action, SIGNAL(triggered()), SLOT(runReplicode()));
    actionCollection()->addAction("katereplicode_run", action);

    m_toolview = mainWindow->createToolView("kate_private_plugin_katereplicodeplugin", Kate::MainWindow::Bottom, SmallIcon("code-block"), i18n("Replicode Output"));
    m_replicodeOutput = new QListWidget(m_toolview);
    m_replicodeOutput->setSelectionMode(QAbstractItemView::ContiguousSelection);
    mainWindow->hideToolView(m_toolview);

    m_settings.userClassPath = "/home/sandsmark/src/replicode/Test/V1.2/user.classes.replicode";
    m_settings.userOperatorPath = "/home/sandsmark/src/replicode/build/usr_operators/libusr_operators.so";

    m_mainWindow->guiFactory()->addClient(this);
}

ReplicodeView::~ReplicodeView()
{
    m_mainWindow->guiFactory()->removeClient(this);
    delete m_executor;
    delete m_settingsFile;
}

void ReplicodeView::runReplicode()
{
    m_mainWindow->showToolView(m_toolview);

    KTextEditor::View *editor = m_mainWindow->activeView();
    if (!editor || !editor->document()) {
        QMessageBox::warning(m_mainWindow->centralWidget(), i18n("Unable to find active file"), i18n("Can't find active file to run!"));
        return;
    }
    QFileInfo sourceFile = QFileInfo(editor->document()->url().toLocalFile());

    KConfigGroup config(KGlobal::config(), "Replicode");
    QString executorPath = config.readEntry<QString>("replicodePath", QString());
    if (executorPath.isEmpty()) {
        QMessageBox::warning(m_mainWindow->centralWidget(), i18n("Can't find replicode executor"), i18n("Unable to find replicode executor.\nPlease go to settings and set the path to the Replicode executor."));
        return;
    }

    if (m_settings.userOperatorPath.isEmpty()) {
        QMessageBox::warning(m_mainWindow->centralWidget(), i18n("Can't find replicode executor"), i18n("Unable to find replicode executor.\nPlease go to settings and set the path to the Replicode executor."));
    }

    if (m_settingsFile) delete m_settingsFile;

    m_settingsFile = new QTemporaryFile;
    if (!m_settingsFile->open()) {
        delete m_settingsFile;
        m_settingsFile = 0;
        QMessageBox::warning(m_mainWindow->window(), tr("Unable to create file"), tr("Unable to create temporary file!"));
    }
    m_settings.writeXml(m_settingsFile, sourceFile.canonicalFilePath());
    m_settingsFile->close();

    qDebug() << "Settings:" << m_settingsFile->fileName() << "Source file:" << sourceFile.canonicalFilePath();

    m_replicodeOutput->clear();

    if (m_executor) delete m_executor;
    m_executor = new QProcess(this);
    m_executor->setWorkingDirectory(sourceFile.canonicalPath());
    connect(m_executor, SIGNAL(readyReadStandardError()), SLOT(gotStderr()));
    connect(m_executor, SIGNAL(readyReadStandardOutput()), SLOT(gotStdout()));
    connect(m_executor, SIGNAL(finished(int)), SLOT(replicodeFinished()));
    connect(m_executor, SIGNAL(error(QProcess::ProcessError)), SLOT(runErrored(QProcess::ProcessError)));
    qDebug() << executorPath << sourceFile.canonicalPath();
    m_executor->start(executorPath, QStringList() << m_settingsFile->fileName(), QProcess::ReadOnly);
}

void ReplicodeView::runErrored(QProcess::ProcessError error)
{
}

void ReplicodeView::replicodeFinished()
{
//    delete m_executor;
//    delete m_settingsFile;
//    m_executor = 0;
//    m_settingsFile = 0;
}

void ReplicodeView::gotStderr()
{
    QString output = m_executor->readAllStandardError();
    foreach(QString line, output.split('\n')) {
        line = line.simplified();
        if (line.isEmpty()) continue;
        QListWidgetItem *item = new QListWidgetItem(line);
        item->setForeground(Qt::red);
        m_replicodeOutput->addItem(item);
    }
    m_replicodeOutput->scrollToBottom();
}

void ReplicodeView::gotStdout()
{
    QString output = m_executor->readAllStandardOutput();
    foreach(QString line, output.split('\n')) {
        line = line.simplified();
        if (line.isEmpty()) continue;
        m_replicodeOutput->addItem(line);
    }
    m_replicodeOutput->scrollToBottom();
}

#include "replicodeview.moc"
#include "replicodeplugin.moc"
