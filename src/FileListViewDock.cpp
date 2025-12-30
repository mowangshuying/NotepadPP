#include "FileListViewDock.h"

FileListViewDock::FileListViewDock(QWidget *parent) : QDockWidget(parent)
{
    __initUI();
}

FileListViewDock::~FileListViewDock()
{
}

void FileListViewDock::__initUI()
{
    setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    setAttribute(Qt::WA_DeleteOnClose);

    m_pFileListView = new FileListView(this);
    // m_pFileListView->setNotePad(this);
    setWidget(m_pFileListView);
}

void FileListViewDock::addFilePath(QString filepath)
{
    m_pFileListView->addItem(filepath);
}

void FileListViewDock::delFilePath(QString filepath)
{
    m_pFileListView->delItem(filepath);
}

void FileListViewDock::setNotePad(QWidget *notepad)
{
    m_pFileListView->setNotePad(this);
}
