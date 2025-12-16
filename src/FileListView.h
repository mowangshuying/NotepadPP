#pragma once
#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>

class FileListViewItem;
class FileListView : public QWidget
{
    Q_OBJECT
public:
    FileListView(QWidget *parent = nullptr);

    void setNotePad(QWidget* pNotePad);

    FileListViewItem* findItem(QString filepath);

    void addItem(QString filepath);

    void delItem(QString filepath);

    void setCurItem(QString filepath);

    void sortItems();
// public slots:
    void onItemClicked(QListWidgetItem* item);
protected:
    QListWidget* m_filelistWidget;
    QVBoxLayout* m_vMainLayout;
    QWidget* m_notepad;
};