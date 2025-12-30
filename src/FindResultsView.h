#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include "FindRecords.h"

class TreeView;
class FindResultsView : public QWidget
{
    Q_OBJECT
  public:
    FindResultsView(QWidget* parent = nullptr);

    void __initUI();

    void appendResultsToShow(FindRecords* findRecords);

  protected:
    TreeView* m_treeView;
    QVBoxLayout* m_vMainLayout;
};