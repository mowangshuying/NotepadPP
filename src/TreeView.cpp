#include "TreeView.h"
#include <QHeaderView>
#include "__global.h"

TreeView::TreeView(QWidget *parent)
{
    __initUI();

    m_model = new QStandardItemModel(this);
    m_delegate = new HtmlStyledItemDelegate(this);
    setItemDelegate(m_delegate);
    setModel(m_model);
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

void TreeView::setItemBackgroundColor(QStandardItem *item, QColor color)
{
    QBrush brush(color);
    item->setBackground(brush);
}

void TreeView::appendResultsToShow(FindRecords *findRecords)
{
    if (findRecords == nullptr)
    {
        return;
    }

    QString findTitle;
    findTitle = tr("<font style='font-size:14px;font-weight:bold;color:#343497'>Search \"%1\" (%2 hits)</font>")
        .arg(findRecords->getFindText().toHtmlEscaped()).arg(findRecords->getFindRecordList().size());

    QStandardItem* titleItem = new QStandardItem(findTitle);
    setItemBackgroundColor(titleItem, QColor(0xbbbbfff));

    m_model->insertRow(0, titleItem);
    titleItem->setData(true, (int)(SelfUserRole::ResultItemRoot));

    ///  收缩其他的行显示第一行
    for (int i = 1; i < m_model->rowCount(); i++)
    {
        collapse(m_model->index(i, 0));
    }

    expand(m_model->index(0, 0));

    if (findRecords->getFindRecordList().size() == 0)
    {
        return;
    }

    QString desc;
    desc = tr("<font style='font-size:14px;color:#99cc99'>%1 (%2 hits)</font>")
        .arg(findRecords->getFindFilePath().toHtmlEscaped()).arg(findRecords->getFindRecordList().size());

    QStandardItem* descItem = new QStandardItem(desc);
    setItemBackgroundColor(descItem, QColor(0x484848));
    titleItem->appendRow(descItem);

    descItem->setData((qlonglong)findRecords->getEditView(), (int)(SelfUserRole::ResultItemEditor));
    descItem->setData(findRecords->getFindFilePath(), (int)(SelfUserRole::ResultItemEditorFilePath));
    descItem->setData(findRecords->getFindText(), (int)(SelfUserRole::ResultItemWhatFind));
    descItem->setData(true, (int)(SelfUserRole::ResultItemDesc));

    for (int i = 0; i < findRecords->getFindRecordList().size(); i++)
    {
        
        FindRecord findRecord = findRecords->getFindRecordList().at(i);
        QString richText = highLightFindText(findRecord);
        QString text;
        text = tr("<font style='font-size:14px;color:#ffffff'>Line </font><font style='font-size:14px;color:#ff8040'>%1</font> : %2").arg(findRecord.getLineNums()+ 1).arg(richText);

        QStandardItem* childItem = new QStandardItem(text);
        childItem->setData(findRecord.getLineStartPos(), (int)(SelfUserRole::ResultItemPos));
        childItem->setData(findRecord.getTargetEndPos() - findRecord.getTargetStartPos(), (int)(SelfUserRole::ResultItemLen));
        descItem->appendRow(childItem);
    }

    if (!findRecords->getFindRecordList().isEmpty())
    {
        expand(m_model->index(0, 0, m_model->index(0, 0)));
    }
}

QString TreeView::highLightFindText(FindRecord &record)
{
    // return QString();
    QByteArray utf8Bytes = record.getLineContents().toUtf8();
    int lineLens = utf8Bytes.length();

    int targetStartPos = record.getTargetStartPos() - record.getLineStartPos();
    int targetLens = record.getTargetEndPos()- record.getTargetStartPos();
    int tailStart = record.getTargetEndPos() - record.getLineStartPos();

    QString head = QString(utf8Bytes.mid(0, targetStartPos)).toHtmlEscaped();
    QString target = QString(utf8Bytes.mid(targetStartPos, targetLens)).toHtmlEscaped();
    QString tail = QString(utf8Bytes.mid(tailStart)).toHtmlEscaped();

    // head = QString::asprintf("<font style='font-size:14px;'>%s</font>",  head.toStdString().c_str());
    // target = QString::asprintf("<font style='font-size:14px;background-color:#ffffbf'>%s</font>", target.toStdString().c_str());
    // tail = QString::asprintf("<font style='font-size:14px;'>%s</font>", tail.toStdString().c_str());

    // 改为arg模式
    head = tr("<font style='font-size:14px;'>%1</font>").arg(head);
    target = tr("<font style='font-size:14px;background-color:#ffffbf'>%1</font>").arg(target);
    tail = tr("<font style='font-size:14px;'>%1</font>").arg(tail);


    return QString("%1%2%3").arg(head, target, tail);

}

void TreeView::__onPressed(QModelIndex modeIndex)
{
    resizeColumnToContents(modeIndex.column());
}

void TreeView::__onExpanded(QModelIndex modeIndex)
{
    resizeColumnToContents(modeIndex.column());
}
