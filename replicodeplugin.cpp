#include "replicodeplugin.h"
#include "replicodeview.h"

#include <KTextEditor/Document>
#include <KTextEditor/View>

#include <KPluginFactory>
#include <KPluginLoader>
#include <KLocale>
#include <KAction>
#include <KActionCollection>

K_PLUGIN_FACTORY(ReplicodePluginFactory, registerPlugin<ReplicodePlugin>("ktexteditor_replicode");)
K_EXPORT_PLUGIN(ReplicodePluginFactory("ktexteditor_replicode", "ktexteditor_plugins"))

ReplicodePlugin::ReplicodePlugin(QObject *parent, const QVariantList &args)
: KTextEditor::Plugin(parent)
{
	Q_UNUSED(args);
}

ReplicodePlugin::~ReplicodePlugin()
{
}

void ReplicodePlugin::addView(KTextEditor::View *view)
{
	ReplicodeView *nview = new ReplicodeView(view);
	m_views.append(nview);
}

void ReplicodePlugin::removeView(KTextEditor::View *view)
{
	for(int z = 0; z < m_views.size(); z++)
	{
		if(m_views.at(z)->parentClient() == view)
		{
			ReplicodeView *nview = m_views.at(z);
			m_views.removeAll(nview);
			delete nview;
		}
	}
}

void ReplicodePlugin::readConfig()
{
}

void ReplicodePlugin::writeConfig()
{
}

ReplicodeView::ReplicodeView(KTextEditor::View *view)
: QObject(view)
, KXMLGUIClient(view)
, m_view(view)
{
	setComponentData(ReplicodePluginFactory::componentData());
	
	KAction *action = new KAction(i18n("KTextEditor - Replicode"), this);
	actionCollection()->addAction("tools_replicode", action);
	//action->setShortcut(Qt::CTRL + Qt::Key_XYZ);
	connect(action, SIGNAL(triggered()), this, SLOT(insertReplicode()));
	
	setXMLFile("replicodeui.rc");
}

ReplicodeView::~ReplicodeView()
{
}

void ReplicodeView::insertReplicode()
{
	m_view->document()->insertText(m_view->cursorPosition(), i18n("Hello, World!"));
}

#include "replicodeview.moc"
