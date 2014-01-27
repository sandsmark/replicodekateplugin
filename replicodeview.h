#ifndef REPLICODEVIEW_H
#define REPLICODEVIEW_H

#include "replicodesettings.h"
#include <QObject>
#include <KXMLGUIClient>
#include <kate/plugin.h>
#include <QProcess>

class QTemporaryFile;
class QProcess;
class QListWidget;

class ReplicodeView : public Kate::PluginView, public Kate::XMLGUIClient
{
	Q_OBJECT

	public:
		explicit ReplicodeView(Kate::MainWindow *mainWindow);
		~ReplicodeView();

	private slots:
		void runReplicode();
        void replicodeFinished();
        void gotStderr();
        void gotStdout();
        void runErrored(QProcess::ProcessError);

	private:
        Kate::MainWindow *m_mainWindow;
        QTemporaryFile *m_settingsFile;
        ReplicodeSettings m_settings;
        QProcess *m_executor;
        QListWidget *m_replicodeOutput;
        QWidget *m_toolview;
};

#endif
