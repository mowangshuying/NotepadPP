#pragma once

#include <QListWidgetItem>

class FileListViewItem : public QListWidgetItem
{
public:
    FileListViewItem(QListWidget* parent = nullptr) 
        : QListWidgetItem(parent) 
    {

    }

    FileListViewItem(const QString& text, QListWidget* parent = nullptr) 
        : QListWidgetItem(text, parent) 
    {

    }

    FileListViewItem(const QIcon& icon, const QString& text, QListWidget* parent = nullptr) 
        : QListWidgetItem(icon, text, parent) 
    {

    }

    void setFilePath(QString filepath) 
    { 
        m_filepath = filepath; 
    }

    QString getFilePath() 
    { 
        return m_filepath; 
    }

protected:
    QString m_filepath; //文件路径
};