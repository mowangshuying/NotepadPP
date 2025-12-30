#pragma once

#include <QDockWidget>
#include "FindRecords.h"

class FindResultsView;
class FindResultsDock : public QDockWidget
{
    Q_OBJECT
  public:
    FindResultsDock(QWidget* parent = nullptr);

    void __connect();

    void appendResultsToShow(FindRecords* findRecords);
signals:
    // 传导至主界面处理信号.
    void itemClicked(const QModelIndex& index);
    void itemDoubleClicked(const QModelIndex& index);
  protected:
    FindResultsView* m_findResultsView;
};