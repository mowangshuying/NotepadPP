#pragma once
#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>

class FileListViewItem;
class FileListView : public QWidget
{
    Q_OBJECT
  public:
    FileListView(QWidget* parent = nullptr);

    void __connect();

    void setNotePad(QWidget* pNotePad);

    FileListViewItem* findItem(QString filepath);

    void addItem(QString filepath);

    void delItem(QString filepath);

    void setCurItem(QString filepath);

    void sortItems();

    void showFileInExplorer(QString path);
    // public slots:
    void onItemClicked(QListWidgetItem* item);

    void onShowPopMenu(const QPoint& pos);

  protected:
    QListWidget* m_filelistWidget;
    QVBoxLayout* m_vMainLayout;
    QWidget* m_notepad;
};