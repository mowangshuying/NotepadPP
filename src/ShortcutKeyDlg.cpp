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

    setFixedSize(900, 600);
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

    // notepad basic shortcut keys
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

    // qsci shortcut keys
    auto moveDownOneLine = ShortcutKeySt(QString(tr("Move Down One Line")), QString("movedownoneline"), QString("Down"), false);
    m_shortcutKeyStVct.push_back(moveDownOneLine);
    auto extendSelectionDownOneLine = ShortcutKeySt(QString(tr("Extend Selection Down One Line")), QString("extendselectiondownoneline"), QString("Shift+Down"), false);
    m_shortcutKeyStVct.push_back(extendSelectionDownOneLine);
    auto extendRectangularSelectionDownOneLine = ShortcutKeySt(QString(tr("Extend Rectangular Selection Down One Line")), QString("extendrectangularselectiondownoneline"), QString("Alt+Shift+Down"), false);
    m_shortcutKeyStVct.push_back(extendRectangularSelectionDownOneLine);
    auto srollviewDownOneLine = ShortcutKeySt(QString(tr("Scroll View Down One Line")), QString("scrollviewdownoneline"), QString("Ctrl+Down"), false);
    m_shortcutKeyStVct.push_back(srollviewDownOneLine);
    auto moveUpOneLine = ShortcutKeySt(QString(tr("Move Up One Line")), QString("moveuponeline"), QString("Up"), false);
    m_shortcutKeyStVct.push_back(moveUpOneLine);
    auto extendSelectionUpOneLine = ShortcutKeySt(QString(tr("Extend Selection Up One Line")), QString("extendselectionuponeline"), QString("Shift+Up"), false);
    m_shortcutKeyStVct.push_back(extendSelectionUpOneLine);
    auto extendRectangularSelectionUpOneLine = ShortcutKeySt(QString(tr("Extend Rectangular Selection Up One Line")), QString("extendrectangularselectionuponeline"), QString("Alt+Shift+Up"), false);
    m_shortcutKeyStVct.push_back(extendRectangularSelectionUpOneLine);
    auto scrollviewUpOneLine = ShortcutKeySt(QString(tr("Scroll View Up One Line")), QString("scrollviewuponeline"), QString("Ctrl+Up"), false);
    m_shortcutKeyStVct.push_back(scrollviewUpOneLine);
    auto moveDownOneParagraph = ShortcutKeySt(QString(tr("Move Down One Paragraph")), QString("movedownoneparagraph"), QString("Ctrl+]"), false);
    m_shortcutKeyStVct.push_back(moveDownOneParagraph);
    auto extendSelectionDownOneParagraph = ShortcutKeySt(QString(tr("Extend Selection Down One Paragraph")), QString("extendselectiondownoneparagraph"), QString("Ctrl+Shift+]"), false);
    m_shortcutKeyStVct.push_back(extendSelectionDownOneParagraph);
    auto moveLeftOneCharacter = ShortcutKeySt(QString(tr("Move Left One Character")), QString("moveleftonecharacter"), QString("Left"), false);
    m_shortcutKeyStVct.push_back(moveLeftOneCharacter);
    auto extendSelectionLeftOneCharacter = ShortcutKeySt(QString(tr("Extend Selection Left One Character")), QString("extendselectionleftonecharacter"), QString("Shift+Left"), false);
    m_shortcutKeyStVct.push_back(extendSelectionLeftOneCharacter);
    auto extendRectangularSelectionLeftOneCharacter = ShortcutKeySt(QString(tr("Extend Rectangular Selection Left One Character")), QString("extendrectangularselectionleftonecharacter"), QString("Alt+Shift+Left"), false);
    m_shortcutKeyStVct.push_back(extendRectangularSelectionLeftOneCharacter);
    auto moveRightOneCharacter = ShortcutKeySt(QString(tr("Move Right One Character")), QString("moverightonecharacter"), QString("Right"), false);
    m_shortcutKeyStVct.push_back(moveRightOneCharacter);
    auto extendSelectionRightOneCharacter = ShortcutKeySt(QString(tr("Extend Selection Right One Character")), QString("extendselectionrightonecharacter"), QString("Shift+Right"), false);
    m_shortcutKeyStVct.push_back(extendSelectionRightOneCharacter);
    auto extendRectangularSelectionRightOneCharacter = ShortcutKeySt(QString(tr("Extend Rectangular Selection Right One Character")), QString("extendrectangularselectionrightonecharacter"), QString("Ctrl+Shift+Right"), false);
    m_shortcutKeyStVct.push_back(extendRectangularSelectionRightOneCharacter);
    auto moveLeftOneWord = ShortcutKeySt(QString(tr("Move Left One Word")), QString("moveleftoneword"), QString("Ctrl+Left"), false);
    m_shortcutKeyStVct.push_back(moveLeftOneWord);
    auto extendSelectionLeftOneWord = ShortcutKeySt(QString(tr("Extend Selection Left One Word")), QString("extendselectionleftoneword"), QString("Ctrl+Shift+Left"), false);
    m_shortcutKeyStVct.push_back(extendSelectionLeftOneWord);
    auto moveRightOneWord = ShortcutKeySt(QString(tr("Move Right One Word")), QString("moverightoneword"), QString("Ctrl+Right"), false);
    m_shortcutKeyStVct.push_back(moveRightOneWord);
    auto extendSelectionRightOneWord = ShortcutKeySt(QString(tr("Extend Selection Right One Word")), QString("extendselectionrightoneword"), QString("Ctrl+Shift+Right"), false);
    m_shortcutKeyStVct.push_back(extendSelectionRightOneWord);
    auto moveLeftOneWordPart = ShortcutKeySt(QString(tr("Move Left One Word Part")), QString("moveleftonewordpart"), QString("Ctrl+Shift+Left"), false);
    m_shortcutKeyStVct.push_back(moveLeftOneWordPart);
    auto extendSelectionLeftOneWordPart = ShortcutKeySt(QString(tr("Extend Selection Left One Word Part")), QString("extendselectionleftonewordpart"), QString("Ctrl+Shift+Left"), false);
    m_shortcutKeyStVct.push_back(extendSelectionLeftOneWordPart);
    auto moveRightOneWordPart = ShortcutKeySt(QString(tr("Move Right One Word Part")), QString("moverightonewordpart"), QString("Ctrl+Shift+Right"), false);
    m_shortcutKeyStVct.push_back(moveRightOneWordPart);
    auto extendSelectionRightOneWordPart = ShortcutKeySt(QString(tr("Extend Selection Right One Word Part")), QString("extendselectionrightonewordpart"), QString("Ctrl+Shift+Right"), false);
    m_shortcutKeyStVct.push_back(extendSelectionRightOneWordPart);
    auto moveToStartOfDisplayLine = ShortcutKeySt(QString(tr("Move To Start Of Display Line")), QString("movetostartofdisplayline"), QString("Home"), false);
    m_shortcutKeyStVct.push_back(moveToStartOfDisplayLine);
    auto moveToFirstVisibleCharacterInDocumentLine = ShortcutKeySt(QString(tr("Move To First Visible Character In Document Line")), QString("movetofirstvisiblecharacterindocumentline"), QString("Home"), false);
    m_shortcutKeyStVct.push_back(moveToFirstVisibleCharacterInDocumentLine);
    auto extendSelectionOfFirstVisibleCharacterInDocumentLine = ShortcutKeySt(QString(tr("Extend Selection Of First Visible Character In Document Line")), QString("extendselectionoffirstvisiblecharacterindocumentline"), QString("Ctrl+Home"), false);
    m_shortcutKeyStVct.push_back(moveToFirstVisibleCharacterInDocumentLine);
    auto extendRectangularSelectionOfFirstVisibleCharacterInDocumentLine = ShortcutKeySt(QString(tr("Extend Rectangular Selection Of First Visible Character In Document Line")), QString("extendrectangularselectionoffirstvisiblecharacterindocumentline"), QString("Ctrl+Shift+Home"), false);
    m_shortcutKeyStVct.push_back(extendRectangularSelectionOfFirstVisibleCharacterInDocumentLine);
    auto moveToEndOfDisplayLine = ShortcutKeySt(QString(tr("Move To End Of Display Line")), QString("movetostartofdisplayline"), QString("End"), false);
    m_shortcutKeyStVct.push_back(moveToEndOfDisplayLine);
    auto moveToStartOfDocument = ShortcutKeySt(QString(tr("Move To Start Of Document")), QString("movetostartofdocument"), QString("Ctrl+Home"), false);
    m_shortcutKeyStVct.push_back(moveToStartOfDocument);
    auto moveToEndOfDocument = ShortcutKeySt(QString(tr("Move To End Of Document")), QString("movetostartofdocument"), QString("Ctrl+End"), false);
    m_shortcutKeyStVct.push_back(moveToEndOfDocument);
    auto extendSelectionToEndOfDocument = ShortcutKeySt(QString(tr("Extend Selection To End Of Document")), QString("extendselectiontoendofdocument"), QString("Ctrl+Shift+End"), false);
    m_shortcutKeyStVct.push_back(extendSelectionToEndOfDocument);
    auto extendSelectionToStartOfDocument = ShortcutKeySt(QString(tr("Extend Selection To Start Of Document")), QString("extendselectiontostartofdocument"), QString("Ctrl+Shift+Home"), false);
    m_shortcutKeyStVct.push_back(extendSelectionToStartOfDocument);
    auto moveDownOnePage = ShortcutKeySt(QString(tr("Move Down One Page")), QString("movedownonepage"), QString("PageDown"), false);
    m_shortcutKeyStVct.push_back(moveDownOnePage);
    auto extendSelectionDownOnePage = ShortcutKeySt(QString(tr("Extend Selection Down One Page")), QString("extendselectiondownonepage"), QString("Ctrl+PageDown"), false);
    m_shortcutKeyStVct.push_back(extendSelectionDownOnePage);
    auto deleteCurrentCharacter = ShortcutKeySt(QString(tr("Delete Current Character")), QString("deletecurrentcharacter"), QString("Delete"), false);
    m_shortcutKeyStVct.push_back(deleteCurrentCharacter);
    auto deletePreviousCharacter = ShortcutKeySt(QString(tr("Delete Previous Character")), QString("deletepreviouscharacter"), QString("Backspace"), false);
    m_shortcutKeyStVct.push_back(deletePreviousCharacter);
    auto deleteWordToLeft = ShortcutKeySt(QString(tr("Delete Word To Left")), QString("deletewordtolft"), QString("Ctrl+Backspace"), false);
    m_shortcutKeyStVct.push_back(deleteWordToLeft);
    auto deleteWordToRight = ShortcutKeySt(QString(tr("Delete Word To Right")), QString("deletewordtoright"), QString("Ctrl+Delete"), false);
    m_shortcutKeyStVct.push_back(deleteWordToRight);
    auto  deleteLineToLeft = ShortcutKeySt(QString(tr("Delete Line To Left")), QString("deletelinetotleft"), QString("Ctrl+Shift+Backspace"), false);
    m_shortcutKeyStVct.push_back(deleteLineToLeft);
    auto deleteLineToRight = ShortcutKeySt(QString(tr("Delete Line To Right")), QString("deletelinetotright"), QString("Ctrl+Shift+Delete"), false);
    m_shortcutKeyStVct.push_back(deleteLineToRight);
    auto deleteCurrentLine = ShortcutKeySt(QString(tr("Delete Current Line")), QString("deletecurrentline"), QString("Ctrl+Shift+L"), false);
    m_shortcutKeyStVct.push_back(deleteCurrentLine);
    auto cutCurrentLine = ShortcutKeySt(QString(tr("Cut Current Line")), QString("cutcurrentline"), QString("Ctrl+L"), false);
    m_shortcutKeyStVct.push_back(cutCurrentLine);
    auto copyCurrentLine = ShortcutKeySt(QString(tr("Copy Current Line")), QString("copycurrentline"), QString("Ctrl+Shift+T"), false);
    m_shortcutKeyStVct.push_back(copyCurrentLine);
    auto selectAll = ShortcutKeySt(QString(tr("Select All")), QString("selectall"), QString("Ctrl+A"), false);
    m_shortcutKeyStVct.push_back(selectAll);
    auto duplicateSelection = ShortcutKeySt(QString(tr("Duplicate Selection")), QString("duplicateselection"), QString("Ctrl+D"), false);
    m_shortcutKeyStVct.push_back(duplicateSelection);
    auto convertSelectionToLowerCase = ShortcutKeySt(QString(tr("Convert Selection To Lower Case")), QString("convertselectiontolowercase"), QString("Ctrl+U"), false);
    m_shortcutKeyStVct.push_back(convertSelectionToLowerCase);
    auto convertSelectionToUpperCase = ShortcutKeySt(QString(tr("Convert Selection To Upper Case")), QString("convertselectiontouppercase"), QString("Ctrl+Shift+U"), false);
    m_shortcutKeyStVct.push_back(convertSelectionToUpperCase);
    auto cutSelection = ShortcutKeySt(QString(tr("Cut Selection")), QString("cutselection"), QString("Ctrl+X"), false);
    m_shortcutKeyStVct.push_back(cutSelection);
    auto copySelection = ShortcutKeySt(QString(tr("Copy Selection")), QString("copyselection"), QString("Ctrl+C"), false);
    m_shortcutKeyStVct.push_back(copySelection);
    // auto paste = ShortcutKeySt(QString(tr("Paste")), QString("paste"), QString("Ctrl+V"), false);
    // m_shortcutKeyStVct.push_back(paste);
    auto toggleInsertOvertype = ShortcutKeySt(QString(tr("Toggle Insert Overtype")), QString("toggleinsertovertype"), QString("Insert"), false);
    m_shortcutKeyStVct.push_back(toggleInsertOvertype);
    auto insertNewLine = ShortcutKeySt(QString(tr("Insert New Line")), QString("insertnewline"), QString("Return"), false);
    m_shortcutKeyStVct.push_back(insertNewLine);
    auto indentOneLevel = ShortcutKeySt(QString(tr("Indent One Level")), QString("indentonelevel"), QString("Tab"), false);
    m_shortcutKeyStVct.push_back(indentOneLevel);
    auto deleteIndentOneLevel = ShortcutKeySt(QString(tr("Delete Indent One Level")), QString("deleteindentonelevel"), QString("Shift+Tab"), false);
    m_shortcutKeyStVct.push_back(deleteIndentOneLevel);
    auto cancel = ShortcutKeySt(QString(tr("Cancel")), QString("cancel"), QString("Esc"), false);
    m_shortcutKeyStVct.push_back(cancel);
    auto undoLastCommand = ShortcutKeySt(QString(tr("Undo Last Command")), QString("undolastcommand"), QString("Ctrl+Z"), false);
    m_shortcutKeyStVct.push_back(undoLastCommand);
    auto redoLastCommand = ShortcutKeySt(QString(tr("Redo Last Command")), QString("redolastcommand"), QString("Ctrl+Y"), false);
    m_shortcutKeyStVct.push_back(redoLastCommand);
    // auto zoomIn = ShortcutKeySt(QString(tr("Zoom In")), QString("zoomin"), QString("Ctrl++"), false);
    // m_shortcutKeyStVct.push_back(zoomIn);
    // auto zoomOut = ShortcutKeySt(QString(tr("Zoom Out")), QString("zoomout"), QString("Ctrl+-"), false);
    // m_shortcutKeyStVct.push_back(zoomOut);
    auto moveLineUp = ShortcutKeySt(QString(tr("Move Line Up")), QString("movelineup"), QString("Ctrl+Shift+Up"), false);
    m_shortcutKeyStVct.push_back(moveLineUp);
    auto moveLineDown = ShortcutKeySt(QString(tr("Move Line Down")), QString("movelinedown"), QString("Ctrl+Shift+Down"), false);
    m_shortcutKeyStVct.push_back(moveLineDown);

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
