#pragma once

#include <QDialog>
#include <QTabWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "FindPage.h"
#include "ReplacePage.h"

class FindReplaceDlg : public QDialog
{
    Q_OBJECT
  public:
    FindReplaceDlg(QWidget* parent = nullptr);

    void setTabWidget(QTabWidget* tabWidget);

    void setNoteWidget(QWidget* pNoteWidget);

    bool getTimeToClose();
    void setTimeToClose(bool bTimeToClose);

    // close event
    void closeEvent(QCloseEvent* event) override;

  protected:
    QVBoxLayout* m_vMainLayout;
    QTabWidget* m_tabWidget;

    FindPage* m_pFindPage;
    ReplacePage* m_pReplacePage;

    // 是时候关闭了
    bool m_bTimeToClose;

    ///
    QWidget* m_pNoteWidget;
};