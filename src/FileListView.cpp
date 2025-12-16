#include "FileListView.h"
#include "FileListViewItem.h"
#include <vector>
#include "NotePadPP.h"

FileListView::FileListView(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("FileListView");

    m_vMainLayout = new QVBoxLayout(this);
    m_vMainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(m_vMainLayout);

    m_filelistWidget = new QListWidget(this);
    m_vMainLayout->addWidget(m_filelistWidget);
}

void FileListView::setNotePad(QWidget *pNotePad)
{
    m_notepad = pNotePad;
}

 FileListViewItem* FileListView::findItem(QString filepath)
{
    // bool bExist = false;
    FileListViewItem* pItem = nullptr;
    for (int i = 0; i < m_filelistWidget->count(); i++)
    {
        auto item = (FileListViewItem*)m_filelistWidget->item(i);
        if (item->getFilePath() == filepath)
        {
            // bExist = true;
            pItem = item;
            break;
        }
    }
    // return bExist;
    return pItem;
}

void FileListView::addItem(QString filepath)
{
    // bool bExist = (filepath);
    FileListViewItem* pItem = findItem(filepath);
    if (pItem != nullptr)
    {
        return;
    }

    FileListViewItem* item = new FileListViewItem(filepath);
    item->setFilePath(filepath);
    m_filelistWidget->addItem(item);
    sortItems();
}

void FileListView::delItem(QString filepath)
{
    FileListViewItem* pItem = findItem(filepath);
    if (!pItem)
    {
        return;
    }
    m_filelistWidget->removeItemWidget(pItem);
    delete pItem;
    sortItems();
}

void FileListView::setCurItem(QString filepath)
{
    FileListViewItem* pItem = findItem(filepath);
    if (!pItem)
    {
        return;
    }
    m_filelistWidget->setCurrentItem(pItem);
    auto pNotePad = dynamic_cast<NotepadPP*>(m_notepad);
    if (!pNotePad)
    {
        return;
    }
    pNotePad->setCurTabByPath(filepath);
}

void FileListView::sortItems()
{
    std::vector<QString> filepaths;
    for (int i = 0; i < m_filelistWidget->count(); i++)瓬
    {
        FileListViewItem* pItem = (FileListViewItem*)m_filelistWidget->item(i);
        filepaths.push_back(pItem->getFilePath());
    }

    std::sort(filepaths.begin(), filepaths.end(), [](QString a, QString b) {return a.toLower() < b.toLower(); });

    for (int i = 0; i < m_filelistWidget->count(); i++)
    {
        FileListViewItem* pItem = (FileListViewItem*)m_filelistWidget->item(i);
        pItem->setFilePath(filepaths[i]);
        pItem->setText(filepaths[i]);
    }
}

void FileListView::onItemClicked(QListWidgetItem *item)
{
    setCurItem(item->text());
}
