#pragma once

#include <QTreeView>
#include "HtmlStyledItemDelegate.h"
#include <QStandardItemModel>
#include "FindRecords.h"
#include <QStandardItem>

class TreeView : public QTreeView
{
    Q_OBJECT
  public:
    TreeView(QWidget* parent = nullptr);

    void __initUI();

    void __connect();

    QModelIndexList getSelectedIndexes();

    void setItemBackgroundColor(QStandardItem* item, QColor color);
    void appendResultsToShow(FindRecords* findRecords);

    QString highLightFindText(FindRecord& record);

    // public slots:
    void __onPressed(const QModelIndex& modeIndex);
    void __onExpanded(const QModelIndex& modeIndex);

signals:
//   void itemClicked(QModelIndex modelIndex);
//   void itemDoubleClicked(QModelIndex modelIndex);  
protected:
    HtmlStyledItemDelegate* m_delegate;
    QStandardItemModel* m_model;
};