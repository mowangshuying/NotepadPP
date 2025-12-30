#include "FindReplaceDlg.h"

FindReplaceDlg::FindReplaceDlg(QWidget *parent) : QDialog(parent), m_bTimeToClose(false)
{
    m_vMainLayout = new QVBoxLayout(this);
    setLayout(m_vMainLayout);

    m_vMainLayout->setContentsMargins(0, 0, 0, 0);
    m_tabWidget = new QTabWidget(this);
    m_vMainLayout->addWidget(m_tabWidget);

    m_pFindPage = new FindPage(this);
    m_tabWidget->addTab(m_pFindPage, "Find");

    m_pReplacePage = new ReplacePage(this);
    m_tabWidget->addTab(m_pReplacePage, "Replace");

    setFixedSize(538, 360);
    setWindowTitle("Find & Replace");
}

void FindReplaceDlg::setTabWidget(QTabWidget *tabWidget)
{
    m_pFindPage->setTabWidget(tabWidget);
}

void FindReplaceDlg::setNoteWidget(QWidget *pNoteWidget)
{
    m_pNoteWidget = pNoteWidget;
    m_pFindPage->setNoteWidget(pNoteWidget);
}

bool FindReplaceDlg::getTimeToClose()
{
    return m_bTimeToClose;
}

void FindReplaceDlg::setTimeToClose(bool bTimeToClose)
{
    m_bTimeToClose = bTimeToClose;
}

void FindReplaceDlg::closeEvent(QCloseEvent *event)
{
    if (m_bTimeToClose)
    {
        QDialog::closeEvent(event);
        return;
    }

    QDialog::hide();
}
