#ifndef REPLICODEPLUGIN_H
#define REPLICODEPLUGIN_H

#include "replicodeview.h"
#include <kate/plugin.h>
#include <kate/pluginconfigpageinterface.h>


class ReplicodePlugin : public Kate::Plugin, public Kate::PluginConfigPageInterface
{
    Q_OBJECT
    Q_INTERFACES(Kate::PluginConfigPageInterface)

  public:
    // Constructor
    explicit ReplicodePlugin(QObject *parent = 0, const QList<QVariant> &args = QList<QVariant>());
    // Destructor
    virtual ~ReplicodePlugin();

    Kate::PluginView *createView(Kate::MainWindow *mainWindow) {
        return new ReplicodeView(mainWindow);
    }

    // Config interface
    uint configPages () const;
    Kate::PluginConfigPage *configPage (uint number = 0, QWidget *parent = 0, const char *name = 0 );
    QString configPageFullName (uint number = 0) const;
    QString configPageName(uint number = 0) const;
    KIcon configPageIcon (uint number = 0) const;
};

#endif
