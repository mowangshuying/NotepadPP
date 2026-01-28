#include "TreeView.h"
#include <QHeaderView>
#include "__global.h"
#include "StyleSheetUtils.h"

TreeView::TreeView(QWidget *parent)
{
    __initUI();

    m_model = new QStandardItemModel(this);
    m_delegate = new HtmlStyledItemDelegate(this);
    setItemDelegate(m_delegate);
    setModel(m_model);

    // setHeaderHidden(true);
    StyleSheetUtils::setQssByFileName(this, ":/res/StyleSheet/TreeView.qss");
}

void TreeView::__initUI()
{
    setLineWidth(1);
    setFrameShape(QFrame::Panel);

    setAnimated(true);
    header()->setVisible(false);

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

    //// 处理重复的记录, 移除重复的记录
    bool bHasRecord = false;
    int nMarkIndex = 0;
    for (int i = 0; i < m_findRecordsVct.size(); i++)
    {
        QString findText = m_findRecordsVct.at(i).getFindText();
        ScintillaEditView *pEdit = m_findRecordsVct.at(i).getEditView();
        if (findRecords->getFindText() == findText && findRecords->getEditView() == pEdit)
        {
            bHasRecord = true;
            nMarkIndex = i;
            break;
        }
    }

    if (bHasRecord)
    {
        // 删除nMarkIndex位置的记录
        m_findRecordsVct.erase(m_findRecordsVct.begin() + nMarkIndex);
        m_model->removeRow(nMarkIndex);
    }

    FindRecords frs;
    frs.setFindFilePath(findRecords->getFindFilePath());
    frs.setFindText(findRecords->getFindText());
    frs.setEditView(findRecords->getEditView());
    m_findRecordsVct.insert(m_findRecordsVct.begin(), frs);

    QString findTitle;
    findTitle = tr("<font style='font-size:14px;font-weight:bold;background-color:#ffffff;color:#3d6acf'>Search \"%1\" (%2 hits)</font>").arg(findRecords->getFindText().toHtmlEscaped()).arg(findRecords->getFindRecordList().size());

    QStandardItem *titleItem = new QStandardItem(findTitle);
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
    desc = tr("<font style='font-size:14px;background-color:#ffffff;color:#3d6acf'>%1 (%2 hits)</font>").arg(findRecords->getFindFilePath().toHtmlEscaped()).arg(findRecords->getFindRecordList().size());

    QStandardItem *descItem = new QStandardItem(desc);
    setItemBackgroundColor(descItem, QColor(0x484848));
    titleItem->appendRow(descItem);

    descItem->setData((qlonglong)(findRecords->getEditView()), (int)(SelfUserRole::ResultItemEditor));
    descItem->setData(findRecords->getFindFilePath(), (int)(SelfUserRole::ResultItemEditorFilePath));
    descItem->setData(findRecords->getFindText(), (int)(SelfUserRole::ResultItemWhatFind));
    descItem->setData(true, (int)(SelfUserRole::ResultItemDesc));

    for (int i = 0; i < findRecords->getFindRecordList().size(); i++)
    {
        FindRecord findRecord = findRecords->getFindRecordList().at(i);
        QString richText = highLightFindText(findRecord);
        QString text;
        text = tr("<font style='font-size:14px;background-color:#ffffff;color:#3d6acf'>Line %1</font>: %2").arg(findRecord.getLineNums() + 1).arg(richText);

        QStandardItem *childItem = new QStandardItem(text);
        childItem->setData(findRecord.getTargetStartPos(), (int)(SelfUserRole::ResultItemPos));
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
    int targetLens = record.getTargetEndPos() - record.getTargetStartPos();
    int tailStart = record.getTargetEndPos() - record.getLineStartPos();

    QString head = QString(utf8Bytes.mid(0, targetStartPos)).toHtmlEscaped();
    QString target = QString(utf8Bytes.mid(targetStartPos, targetLens)).toHtmlEscaped();
    QString tail = QString(utf8Bytes.mid(tailStart)).toHtmlEscaped();

    // 改为arg模式
    head = tr("<font style='font-size:14px;background-color:#ffffff;color:#000000;'>%1</font>").arg(head);
    target = tr("<font style='font-size:14px;background-color:#3d6acf;color:#ffffff'>%1</font>").arg(target);
    tail = tr("<font style='font-size:14px;background-color:#ffffff;color:#000000;'>%1</font>").arg(tail);

    return QString("%1%2%3").arg(head, target, tail);
}

void TreeView::__onPressed(const QModelIndex &modeIndex)
{
    resizeColumnToContents(modeIndex.column());
}

void TreeView::__onExpanded(const QModelIndex &modeIndex)
{
    resizeColumnToContents(modeIndex.column());
}
