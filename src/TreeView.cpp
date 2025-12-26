#include "TreeView.h"
#include <QHeaderView>

TreeView::TreeView(QWidget *parent)
{
    __initUI();
}

void TreeView::__initUI()
{
    setLineWidth(1);
    setFrameShape(QFrame::Panel);

    setAnimated(true);
    header()->setVisible(true);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setEditTriggers(QAbstractItemView::DoubleClicked);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void TreeView::__connect()
{
}

QModelIndexList TreeView::getSelectedIndexes()
{
    return selectedIndexes();
}

void TreeView::__onPressed(QModelIndex modeIndex)
{
    resizeColumnToContents(modeIndex.column());
}

void TreeView::__onExpanded(QModelIndex modeIndex)
{
    resizeColumnToContents(modeIndex.column());
}
