#include "FileListViewItem.h"

FileListViewItem::FileListViewItem(QListWidget* parent /*= nullptr*/) : QListWidgetItem(parent)
{
}

FileListViewItem::FileListViewItem(const QString& text, QListWidget* parent /*= nullptr*/) : QListWidgetItem(text, parent)
{
}

FileListViewItem::FileListViewItem(const QIcon& icon, const QString& text, QListWidget* parent /*= nullptr*/) : QListWidgetItem(icon, text, parent)
{
}

void FileListViewItem::setFilePath(QString filepath)
{
    m_filepath = filepath;
}

QString FileListViewItem::getFilePath()
{
    return m_filepath;
}
