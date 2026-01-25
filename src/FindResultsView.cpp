#include "FindResultsView.h"
#include "TreeView.h"

FindResultsView::FindResultsView(QWidget *parent) : QWidget(parent)
{
    __initUI();
    __connect();
}

void FindResultsView::__initUI()
{
    m_vMainLayout = new QVBoxLayout;
    m_vMainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(m_vMainLayout);

    m_treeView = new TreeView;
    m_vMainLayout->addWidget(m_treeView);
}

void FindResultsView::__connect()
{
    connect(m_treeView, &TreeView::clicked, this, &FindResultsView::itemClicked);
    connect(m_treeView, &TreeView::doubleClicked, this, &FindResultsView::itemDoubleClicked);
}

void FindResultsView::appendResultsToShow(FindRecords *findRecords)
{
    m_treeView->appendResultsToShow(findRecords);
}

void FindResultsView::clearAllContents()
{
}
