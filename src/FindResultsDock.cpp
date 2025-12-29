#include "FindResultsDock.h"
#include "FindResultsView.h"
// #include "FindRecords.h"
FindResultsDock::FindResultsDock(QWidget *parent) : QDockWidget(parent)
{
    m_findResultsView = new FindResultsView;
    setWidget(m_findResultsView);
}

void FindResultsDock::appendResultsToShow(FindRecords *findRecords)
{
    m_findResultsView->appendResultsToShow(findRecords);
}
