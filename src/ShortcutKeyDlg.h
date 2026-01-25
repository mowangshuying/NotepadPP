#pragma once

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include "ShortcutKeySt.h"

class ShortcutKeyDlg : public QDialog
{
    Q_OBJECT
  public:
    ShortcutKeyDlg(QWidget* parent = nullptr);

    void __initUi();

    void __initTable();

    void __initTableData();

  protected:
    QTableWidget* m_tableWidget;
    QVBoxLayout* m_vMainLayout;

    ShortcutKeyStVct m_shortcutKeyStVct;
};