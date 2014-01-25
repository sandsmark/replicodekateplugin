#ifndef REPLICODEVIEW_H
#define REPLICODEVIEW_H

#include <QObject>
#include <KXMLGUIClient>

class ReplicodeView : public QObject, public KXMLGUIClient
{
	Q_OBJECT
	public:
		explicit ReplicodeView(KTextEditor::View *view = 0);
		~ReplicodeView();
	private slots:
		void insertReplicode();
	private:
		KTextEditor::View *m_view;
};

#endif
