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
    FindReplaceDlg(QWidget *parent = nullptr);

protected:
    QVBoxLayout* m_vMainLayout;
    QTabWidget* m_tabWidget;

    FindPage* m_pFindPage;
    ReplacePage* m_pReplacePage;
};