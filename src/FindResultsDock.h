#pragma once

#include <QDockWidget>
#include "FindRecords.h"

class FindResultsView;
class FindResultsDock : public QDockWidget
{
    Q_OBJECT
  public:
    FindResultsDock(QWidget* parent = nullptr);

    void appendResultsToShow(FindRecords* findRecords);

  protected:
    FindResultsView* m_findResultsView;
};