#pragma once

#include <QTreeView>

class TreeView : public QTreeView
{
    Q_OBJECT
public:
    TreeView(QWidget* parent = nullptr);

    void __initUI();

    void __connect();

    QModelIndexList getSelectedIndexes();

    // public slots:
    void __onPressed(QModelIndex modeIndex);
    void __onExpanded(QModelIndex modeIndex);
protected:
} ;