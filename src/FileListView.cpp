#include "FileListView.h"
#include "FileListViewItem.h"
#include <vector>
#include "NotePadPP.h"
#include <QProcess>

FileListView::FileListView(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("FileListView");

    m_vMainLayout = new QVBoxLayout(this);
    m_vMainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(m_vMainLayout);

    m_filelistWidget = new QListWidget(this);
    m_vMainLayout->addWidget(m_filelistWidget);

    setContextMenuPolicy(Qt::CustomContextMenu);

    __connect();
}

void FileListView::__connect()
{
    connect(m_filelistWidget, &QListWidget::itemClicked, this, &FileListView::onItemClicked);
    connect(this, &QListWidget::customContextMenuRequested, this, &FileListView::onShowPopMenu);
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
    for (int i = 0; i < m_filelistWidget->count(); i++)
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

void FileListView::showFileInExplorer(QString path)
{
    QString cmd;

#ifdef _WIN32
	path = path.replace("/", "\\");
	// cmd = QString("explorer.exe /select,%1").arg(path);
    QString program = "explorer.exe";
    QStringList arguments;
    arguments << "/select," << path;
#endif

#ifdef ubu
    path = path.replace("\\", "/");
    QString program = "nautilus";
    QStringList arguments;
    arguments << path;
#endif

#ifdef uos
    path = path.replace("\\", "/");
    QString program = "dde-file-manager";
    QStringList arguments;
    arguments << path;
#endif 

#if defined(Q_OS_MAC)
    path = path.replace("\\", "/");
    QString program = "open";
    QStringList arguments;
    arguments << "-R" << path;
#endif

	QProcess process;
	process.startDetached(program, arguments);
}

void FileListView::onItemClicked(QListWidgetItem *item)
{
    setCurItem(item->text());
}

void FileListView::onShowPopMenu(const QPoint &pos)
{
    auto pItem = dynamic_cast<FileListViewItem*>(m_filelistWidget->itemAt(pos));
    if (!pItem)
    {
        return;
    }

    QMenu* menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    QAction *showFileInExplorerAction = menu->addAction(tr("Show in Explorer"), this, [&](){
        showFileInExplorer(pItem->getFilePath());
    });

    QAction* closeFileAction = menu->addAction(tr("Close File"), this, [&](){
        // delItem(pItem->getFilePath());

        // closeTab(findFileIsOpenAtPad(pItem->getFilePath()));
        auto pNotePad = dynamic_cast<NotepadPP*>(m_notepad);
        int nIndex = pNotePad->findFileIsOpenAtPad(pItem->getFilePath());
        if (nIndex != -1)
        {
            pNotePad->closeTab(nIndex);
        }
    });

    menu->exec(QCursor::pos());
}
