#include "ShortcutKeyDlg.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QString>

ShortcutKeyDlg::ShortcutKeyDlg(QWidget* parent) : QDialog(parent)
{
    __initUi();
    __initTable();
}

void ShortcutKeyDlg::__initUi()
{
    m_vMainLayout = new QVBoxLayout;
    m_vMainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(m_vMainLayout);

    m_tableWidget = new QTableWidget(this);
    m_vMainLayout->addWidget(m_tableWidget);

    setFixedSize(600, 400);
}

void ShortcutKeyDlg::__initTable()
{
    // 设置表格列数
    m_tableWidget->setColumnCount(3);
    m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    __initTableData();
}

void ShortcutKeyDlg::__initTableData()
{

    // header
    QTableWidgetItem* functionWidgetItem = new QTableWidgetItem;
    functionWidgetItem->setText("Function");
    m_tableWidget->setHorizontalHeaderItem(0, functionWidgetItem);

    // shortcut key
    QTableWidgetItem* shortcutKeyWidgetItem = new QTableWidgetItem;
    shortcutKeyWidgetItem->setText("Shortcut Key");
    m_tableWidget->setHorizontalHeaderItem(1, shortcutKeyWidgetItem);

    // description
    QTableWidgetItem* descriptionWidgetItem = new QTableWidgetItem;
    descriptionWidgetItem->setText("Description");
    m_tableWidget->setHorizontalHeaderItem(2, descriptionWidgetItem);

    // data;
    auto newfile = ShortcutKeySt(QString(tr("New File")), QString("newfile"), QString("Ctrl+T"), false);
    m_shortcutKeyStVct.push_back(newfile);
    auto openfile = ShortcutKeySt(QString(tr("Open File")), QString("openfile"), QString("Ctrl+O"), false);
    m_shortcutKeyStVct.push_back(openfile);
    auto savefile = ShortcutKeySt(QString(tr("Save File")), QString("savefile"), QString("Ctrl+S"), false);
    m_shortcutKeyStVct.push_back(savefile);
    auto saveasfile = ShortcutKeySt(QString(tr("Save As")), QString("saveasfile"), QString("Ctrl+Shift+S"), false);
    m_shortcutKeyStVct.push_back(saveasfile);
    auto close = ShortcutKeySt(QString(tr("Close")), QString("close"), QString("Ctrl+W"), false);
    m_shortcutKeyStVct.push_back(close);
    auto cut = ShortcutKeySt(QString(tr("Cut")), QString("cut"), QString("Ctrl+X"), false);
    m_shortcutKeyStVct.push_back(cut);
    auto copy = ShortcutKeySt(QString(tr("Copy")), QString("copy"), QString("Ctrl+C"), false);
    m_shortcutKeyStVct.push_back(copy);
    auto paste = ShortcutKeySt(QString(tr("Paste")), QString("paste"), QString("Ctrl+V"), false);
    m_shortcutKeyStVct.push_back(paste);
    auto undo = ShortcutKeySt(QString(tr("Undo")), QString("undo"), QString("Ctrl+Z"), false);
    m_shortcutKeyStVct.push_back(undo);
    auto redo = ShortcutKeySt(QString(tr("Redo")), QString("redo"), QString("Ctrl+Y"), false);
    m_shortcutKeyStVct.push_back(redo);
    auto find = ShortcutKeySt(QString(tr("Find")), QString("find"), QString("Ctrl+F"), false);
    m_shortcutKeyStVct.push_back(find);

    auto zoomIn = ShortcutKeySt(QString(tr("Zoom In")), QString("zoomin"), QString("Ctrl++"), false);
    m_shortcutKeyStVct.push_back(zoomIn);
    auto zoomOut = ShortcutKeySt(QString(tr("Zoom Out")), QString("zoomout"), QString("Ctrl+-"), false);
    m_shortcutKeyStVct.push_back(zoomOut);
    auto wordWrap = ShortcutKeySt(QString(tr("Word Wrap")), QString("wordwrap"), QString(""), false);
    m_shortcutKeyStVct.push_back(wordWrap);
    auto showBlank = ShortcutKeySt(QString(tr("Show Blank")), QString("showblank"), QString(""), false);
    m_shortcutKeyStVct.push_back(showBlank);
    auto indentGuide = ShortcutKeySt(QString(tr("Indent Guide")), QString("indentguide"), QString(""), false);
    m_shortcutKeyStVct.push_back(indentGuide);

    for (auto& shortcutKeySt : m_shortcutKeyStVct)
    {
        m_tableWidget->insertRow(m_tableWidget->rowCount());
        QTableWidgetItem* functionWidgetItem = new QTableWidgetItem;
        functionWidgetItem->setText(shortcutKeySt.getName());
        m_tableWidget->setItem(m_tableWidget->rowCount() - 1, 0, functionWidgetItem);

        QTableWidgetItem* shortcutKeyWidgetItem = new QTableWidgetItem;
        shortcutKeyWidgetItem->setText(shortcutKeySt.getShortcut().toString());
        m_tableWidget->setItem(m_tableWidget->rowCount() - 1, 1, shortcutKeyWidgetItem);

        QTableWidgetItem* descriptionWidgetItem = new QTableWidgetItem;
        descriptionWidgetItem->setText(shortcutKeySt.getCanModify() ? tr("editable") : tr("can't edit"));
        m_tableWidget->setItem(m_tableWidget->rowCount() - 1, 2, descriptionWidgetItem);
    }
}
