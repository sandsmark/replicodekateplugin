#ifndef REPLICODECONFIG_H
#define REPLICODECONFIG_H

#include <QTabWidget>

class Ui_tabWidget;
class ReplicodeSettings;

class ReplicodeConfig : public QTabWidget
{
    Q_OBJECT
public:
    explicit ReplicodeConfig(QWidget *parent = 0);
    virtual ~ReplicodeConfig();

public slots:
    void reset();
    void save();
    void load();

private:
    Ui_tabWidget *m_ui;
    ReplicodeSettings *m_settings;
};

#endif//REPLICODECONFIG_H