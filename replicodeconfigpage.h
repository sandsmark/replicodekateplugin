#ifndef REPLICODEPLUGINCONFIGPAGE_H
#define REPLICODEPLUGINCONFIGPAGE_H
#include <kate/pluginconfigpageinterface.h>

class KUrlRequester;
class ReplicodeConfig;

class ReplicodeConfigPage : public Kate::PluginConfigPage
{
    Q_OBJECT

public:
    ReplicodeConfigPage(QWidget *parent = 0, const char *name = 0);

public slots:
    void apply();
    void reset();
    void defaults();

private:
    KUrlRequester *m_requester;
    ReplicodeConfig *m_config;
};

#endif//REPLICODEPLUGINCONFIGPAGE_H