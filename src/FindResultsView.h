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

    void __connect();

    void appendResultsToShow(FindRecords* findRecords);

  signals:
    // 传导至主界面处理信号.
    void itemClicked(const QModelIndex& index);
    void itemDoubleClicked(const QModelIndex& index);
  protected:
    TreeView* m_treeView;
    QVBoxLayout* m_vMainLayout;
};