#pragma once

#include <QDialog>
#include <QTabWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

class FindDlg : public QDialog
{ 
    Q_OBJECT
public:
    FindDlg(QWidget *parent = nullptr);

protected:
    QHBoxLayout* m_hMainLayout;
    QTabWidget* m_tabWidget;
};