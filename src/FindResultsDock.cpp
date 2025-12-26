#include "FindResultsDock.h"
#include "FindResultsView.h"

FindResultsDock::FindResultsDock(QWidget *parent) : QDockWidget(parent)
{
    m_findResultsView = new FindResultsView;
    setWidget(m_findResultsView);
}