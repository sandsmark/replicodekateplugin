#ifndef REPLICODEPLUGIN_H
#define REPLICODEPLUGIN_H

#include <KTextEditor/Plugin>

namespace KTextEditor
{
	class View;
}

class ReplicodeView;

class ReplicodePlugin
  : public KTextEditor::Plugin
{
  public:
    // Constructor
    explicit ReplicodePlugin(QObject *parent = 0, const QVariantList &args = QVariantList());
    // Destructor
    virtual ~ReplicodePlugin();

    void addView (KTextEditor::View *view);
    void removeView (KTextEditor::View *view);
 
    void readConfig();
    void writeConfig();
 
//     void readConfig (KConfig *);
//     void writeConfig (KConfig *);
 
  private:
    QList<class ReplicodeView*> m_views;
};

#endif
