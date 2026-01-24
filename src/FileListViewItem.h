#pragma once

#include <QListWidgetItem>

class FileListViewItem : public QListWidgetItem
{
  public:
    FileListViewItem(QListWidget* parent = nullptr);

    FileListViewItem(const QString& text, QListWidget* parent = nullptr);

    FileListViewItem(const QIcon& icon, const QString& text, QListWidget* parent = nullptr);

    void setFilePath(QString filepath);

    QString getFilePath();

  protected:
    QString m_filepath;  // 文件路径
};