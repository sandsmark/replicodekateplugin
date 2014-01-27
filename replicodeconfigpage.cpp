#include "replicodeconfigpage.h"
#include "replicodeconfig.h"
#include <KUrlRequester>
#include <KConfigGroup>
#include <KConfig>

#include <QGridLayout>
#include <QLayout>
#include <klocalizedstring.h>
#include <QLabel>
#include <QTabWidget>

ReplicodeConfigPage::ReplicodeConfigPage(QWidget *parent, const char *name) : Kate::PluginConfigPage(parent, name), m_config(new ReplicodeConfig(this))
{
    QGridLayout *gridlayout = new QGridLayout;
    setLayout(gridlayout);
    gridlayout->addWidget(new QLabel(i18n("Path to replicode executor:")), 0, 0);

    m_requester = new KUrlRequester;
    m_requester->setMode(KFile::File | KFile::ExistingOnly);
    gridlayout->addWidget(m_requester, 0, 1);

    gridlayout->addWidget(m_config, 1, 0, 1, 2);

    reset();

    connect(m_requester, SIGNAL(textChanged(QString)), SIGNAL(changed()));
}

void ReplicodeConfigPage::apply()
{
    KConfigGroup config(KGlobal::config(), "Replicode");
    config.writeEntry("replicodePath", m_requester->text());
    m_config->save();
}

void ReplicodeConfigPage::reset()
{
    KConfigGroup config(KGlobal::config(), "Replicode");
    m_requester->setText(config.readEntry<QString>("replicodePath", QString()));
    m_config->load();
}

void ReplicodeConfigPage::defaults()
{
    m_requester->setText(QString());
    m_config->reset();
}

#include "replicodeconfigpage.moc"