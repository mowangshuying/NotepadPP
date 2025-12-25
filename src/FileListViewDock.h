#pragma once

#include <QDockWidget>
// #include "FileListViewDock.h"
#include "FileListView.h"

class FileListViewDock : public QDockWidget
{ 
    Q_OBJECT
public:
    FileListViewDock(QWidget *parent = nullptr);
    ~FileListViewDock();
    
    void __initUI();

    void addFilePath(QString filepath);
    void delFilePath(QString filepath);

private:
    FileListView* m_pFileListView;
};