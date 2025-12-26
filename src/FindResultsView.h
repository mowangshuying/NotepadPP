#pragma once


#include <QWidget>
#include <QVBoxLayout>

class TreeView;
class FindResultsView : public QWidget {
    Q_OBJECT
public:
    FindResultsView(QWidget* parent = nullptr);

    void __initUI();
protected:
    TreeView* m_treeView;
    QVBoxLayout* m_vMainLayout;
};