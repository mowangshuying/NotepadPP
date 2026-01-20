#include "FindPage.h"
#include <QGroupBox>
#include <QDebug>
#include "ScintillaEditView.h"
#include <Qsci/qsciscintilla.h>
#include <QMessageBox>
#include "FindRecords.h"
#include "NotePadPP.h"

FindPage::FindPage(QWidget* parent)
    : QWidget(parent),
      m_editTabWidget(nullptr),
      m_sFindExpr(""),
      m_bReverseSearch(false),
      m_bMatchWholeWord(false),
      m_bMatchCase(false),
      m_bLoopSearch(false),
      m_bNormal(false),
      m_bExended(false),
      m_bRegularExpression(false),
      m_bFirstFind(true),
      m_pNotepadWidget(nullptr)
{
    // if (parent != nullptr)
    // {
    //     setNoteWidget(parent);
    // }

    __initUI();
    __connect();
}

void FindPage::__initUI()
{
    m_vMainLayout = new QVBoxLayout(this);
    setLayout(m_vMainLayout);
    setContentsMargins(0, 0, 0, 0);
    m_vMainLayout->setSpacing(3);

    // find target;
    auto hFindTargetLayout = new QHBoxLayout();
    m_findTargetLabel = new QLabel(tr("Find Target:"));
    m_findTargetLabel->setFixedWidth(120);
    m_findTargetComboBox = new QComboBox();
    // 可编辑
    m_findTargetComboBox->setEditable(true);
    hFindTargetLayout->addWidget(m_findTargetLabel);
    hFindTargetLayout->addWidget(m_findTargetComboBox, 1);
    m_vMainLayout->addLayout(hFindTargetLayout);

    auto hGroupLayout = new QHBoxLayout();
    auto selectOptionGroup = new QGroupBox();
    auto modeOptionLayout = new QGroupBox();

    auto vSelectOptionLayout = new QVBoxLayout();
    auto vModeOptionLayout = new QVBoxLayout();

    selectOptionGroup->setLayout(vSelectOptionLayout);
    modeOptionLayout->setLayout(vModeOptionLayout);

    hGroupLayout->addWidget(selectOptionGroup);
    hGroupLayout->addWidget(modeOptionLayout);
    m_vMainLayout->addLayout(hGroupLayout);

    // 反向查找
    m_reverseSearchCheckBox = new QCheckBox(tr("Reverse Search"));
    vSelectOptionLayout->addWidget(m_reverseSearchCheckBox);

    // 全词匹配
    m_machWholeWordCheckBox = new QCheckBox(tr("Whole Word Match"));
    vSelectOptionLayout->addWidget(m_machWholeWordCheckBox);

    // 大小写匹配
    m_matchCaseCheckBox = new QCheckBox(tr("Match Case"));
    vSelectOptionLayout->addWidget(m_matchCaseCheckBox);

    // 循环查找
    m_loopSearchCheckBox = new QCheckBox(tr("Loop Search"));
    vSelectOptionLayout->addWidget(m_loopSearchCheckBox);

    // m_vMainLayout->addSpacing(10);

    // 普通·
    m_normalRadioButton = new QRadioButton(tr("Normal"));
    vModeOptionLayout->addWidget(m_normalRadioButton);
    // 扩展·
    m_extendedRadioButton = new QRadioButton(tr("Extended"));
    vModeOptionLayout->addWidget(m_extendedRadioButton);
    // 正则表达式
    m_regexRadioButton = new QRadioButton(tr("Regular Expression"));
    vModeOptionLayout->addWidget(m_regexRadioButton);

    m_vMainLayout->addSpacing(10);

    // 查找下一个
    m_findNextButton = new QPushButton(tr("Find Next"));
    m_findNextButton->setFixedWidth(150);
    m_vMainLayout->addWidget(m_findNextButton);
    // 查找上一个
    m_findPrevButton = new QPushButton(tr("Find Prev"));
    m_findPrevButton->setFixedWidth(150);
    m_vMainLayout->addWidget(m_findPrevButton);
    // 计数
    m_findCountButton = new QPushButton(tr("Count"));
    m_findCountButton->setFixedWidth(150);
    m_vMainLayout->addWidget(m_findCountButton);
    // 在文件中查找
    m_findInCurFileButton = new QPushButton(tr("Find In Current File"));
    m_findInCurFileButton->setFixedWidth(150);
    m_vMainLayout->addWidget(m_findInCurFileButton);

    // 查找所有打开文件
    m_findInAllFileButton = new QPushButton(tr("Find In All Open Files"));
    m_findInAllFileButton->setFixedWidth(150);
    m_vMainLayout->addWidget(m_findInAllFileButton);

    // 清空
    m_clearButton = new QPushButton(tr("Clear"));
    m_clearButton->setFixedWidth(150);
    m_vMainLayout->addWidget(m_clearButton);

    m_vMainLayout->addStretch();
}

void FindPage::__connect()
{
    connect(m_findNextButton, &QPushButton::clicked, this, &FindPage::__onClickedFindNextButton);
    connect(m_findPrevButton, &QPushButton::clicked, this, &FindPage::__onClickedFindPrevButton);
    connect(m_findCountButton, &QPushButton::clicked, this, &FindPage::__onclickedFindCountButton);
    connect(m_findInCurFileButton, &QPushButton::clicked, this, &FindPage::__onClickedFindInCurFileButton);

    // auto pNotepad = dynamic_cast<NotepadPP*>(m_pNotepadWidget);
    // connect(this, &FindPage::showFindRecords, pNotepad, &NotepadPP::__onShowFindRecords);
    connect(m_clearButton, &QPushButton::clicked, this, &FindPage::__onClickedClearButton);
}

ScintillaEditView* FindPage::autoAdjustCurrentEditWin()
{
    // return nullptr;
    auto pEdit = dynamic_cast<ScintillaEditView*>(m_editTabWidget->currentWidget());
    if (pEdit == nullptr)
        return nullptr;

    if (pEdit != m_curEditView)
    {
        m_bFirstFind = true;
        m_curEditView = pEdit;
    }
    return pEdit;
}

void FindPage::setTabWidget(QTabWidget* tabWidget)
{
    m_editTabWidget = tabWidget;
}

void FindPage::setNoteWidget(QWidget* pNoteWidget)
{
    m_pNotepadWidget = pNoteWidget;
    auto pNotepad = dynamic_cast<NotepadPP*>(m_pNotepadWidget);
    disconnect(this, &FindPage::showFindRecords, pNotepad, &NotepadPP::__onShowFindRecords);
    connect(this, &FindPage::showFindRecords, pNotepad, &NotepadPP::__onShowFindRecords);
}

void FindPage::updateParamsFromUI()
{
    // 查找窗口
    // 需要查找的内容
    if (m_findTargetComboBox->currentText() != m_sFindExpr)
    {
        m_sFindExpr = m_findTargetComboBox->currentText();
        m_bFirstFind = true;
    }

    // 正则;
    // m_bRegularExpression = false;
    if (m_regexRadioButton->isChecked() != m_bRegularExpression)
    {
        m_bRegularExpression = m_regexRadioButton->isChecked();
    }

    // 反向查找
    if (m_reverseSearchCheckBox->isChecked() != m_bReverseSearch)
    {
        m_bReverseSearch = m_reverseSearchCheckBox->isChecked();
        m_bFirstFind = true;
    }

    // 匹配整个字符
    if (m_machWholeWordCheckBox->isChecked() != m_bMatchWholeWord)
    {
        m_bMatchWholeWord = m_machWholeWordCheckBox->isChecked();
        m_bFirstFind = true;
    }

    // 匹配大小写
    if (m_matchCaseCheckBox->isChecked() != m_bMatchCase)
    {
        m_bMatchCase = m_matchCaseCheckBox->isChecked();
        m_bFirstFind = true;
    }

    // 循环查找
    if (m_loopSearchCheckBox->isChecked() != m_bLoopSearch)
    {
        m_bLoopSearch = m_loopSearchCheckBox->isChecked();
        m_bFirstFind = true;
    }
}

FindRecord FindPage::getFindRecordFromLastFindState()
{
    FindRecord findRecord;
    ScintillaEditView* pEdit = autoAdjustCurrentEditWin();
    if (pEdit == nullptr)
    {
        return findRecord;
    }

    ScintillaEditView::FindState findState = pEdit->getLastFindState();

    long targetStart = pEdit->execute(SCI_GETTARGETSTART);
    long targetEnd = pEdit->execute(SCI_GETTARGETEND);
    long linenum = pEdit->execute(SCI_LINEFROMPOSITION, targetStart);
    long lineStart = pEdit->execute(SCI_POSITIONFROMLINE, linenum);

    long lineLength = pEdit->execute(SCI_LINELENGTH, linenum);
    char* lineText = new char[lineLength + 1];
    memset(lineText, 0, lineLength + 1);
    pEdit->execute(SCI_GETLINE, linenum, (sptr_t)lineText);
    QString sLineText = QString::fromUtf8(lineText);
    sLineText = delEndofLine(sLineText);

    findRecord.setTargetStartPos(targetStart);
    findRecord.setTargetEndPos(targetEnd);
    findRecord.setLineNums(linenum);
    findRecord.setLineStartPos(lineStart);
    findRecord.setLineContents(sLineText);
    return findRecord;
}

QString FindPage::delEndofLine(QString lineText)
{
    // return QString();
    if (lineText.endsWith("\r\n"))
    {
        return lineText.mid(0, lineText.length() - 2);
    }
    if (lineText.endsWith("\r"))
    {
        return lineText.mid(0, lineText.length() - 1);
    }
    if (lineText.endsWith("\n"))
    {
        return lineText.mid(0, lineText.length() - 1);
    }
    return lineText;
}

void FindPage::__onClickedFindNextButton()
{
    qDebug() << "FindPage::__onClickedFindNextButton()";
    QString findText = m_findTargetComboBox->currentText();
    if (findText.isEmpty())
    {
        return;
    }

    ScintillaEditView* pEdit = autoAdjustCurrentEditWin();
    updateParamsFromUI();

    // if (m_bFindNext == false)
    // {
    // m_bFindNext = true;
    // m_bFirstFind = true;
    // }

    if (m_lastClickedButtonType == LastClickedButtonType::FindPrev)
    {
        m_bFirstFind = true;
    }

    if (m_bFirstFind)
    {
        //  const QString &expr,
        //  bool re,  // 是否使用正则表达式
        //  bool cs,  // 区分大小写
        //  bool wo,  // 全词匹配
        // bool wrap, // 循环查找
        //  bool forward,  // 向前
        //  int line,
        //  int index,

        //  bool show, // 是否显示
        //  bool posix, //
        //  bool cxx11 //
        bool bFind = pEdit->findFirst(findText, m_bRegularExpression, m_bMatchCase, m_bMatchWholeWord, m_bLoopSearch, !m_bReverseSearch, -1, -1, true, false, false);
        if (!bFind)
        {
            qDebug() << "find failed";
            m_bFirstFind = true;
            return;
        }
        else
        {
            m_bFirstFind = false;
        }
    }
    else
    {
        bool bFind = pEdit->findNext();
        if (!bFind)
        {
            qDebug() << "Not found";
        }
    }

    m_lastClickedButtonType = LastClickedButtonType::FindNext;
}

void FindPage::__onClickedFindPrevButton()
{
    qDebug() << "FindPage::__onClickedFindPrevButton()";
    QString findText = m_findTargetComboBox->currentText();
    if (findText.isEmpty())
    {
        return;
    }

    ScintillaEditView* pEdit = autoAdjustCurrentEditWin();
    updateParamsFromUI();

    bool bForward = !m_bReverseSearch;
    if (m_lastClickedButtonType == LastClickedButtonType::FindNext)
    {
        bForward = !bForward;
        m_bFirstFind = true;
    }

    if (m_bFirstFind)
    {
        bool bFind = pEdit->findFirst(findText, m_bRegularExpression, m_bMatchCase, m_bMatchWholeWord, m_bLoopSearch, bForward, -1, -1, true, false, false);
        if (!bFind)
        {
            qDebug() << "find failed";
            m_bFirstFind = true;
            return;
        }
        else
        {
            m_bFirstFind = false;
        }
    }
    else
    {
        bool bFind = pEdit->findNext();
        if (!bFind)
        {
            qDebug() << "Not found";
        }
    }

    m_lastClickedButtonType = LastClickedButtonType::FindPrev;
}

void FindPage::__onclickedFindCountButton()
{
    qDebug() << "FindPage::__onclickedFindCountButton()";
    QString findText = m_findTargetComboBox->currentText();
    if (findText.isEmpty())
    {
        return;
    }

    ScintillaEditView* pEdit = autoAdjustCurrentEditWin();
    updateParamsFromUI();

    int nBakCurrentPos = pEdit->execute(SCI_GETCURRENTPOS);
    int nBakFirstVisibleLine = pEdit->execute(SCI_GETFIRSTVISIBLELINE);

    int nFindCount = 0;

    if (!pEdit->findFirst(findText, m_bRegularExpression, m_bMatchCase, m_bMatchWholeWord, m_bLoopSearch, true, 0, 0, false, false, false))
    {
        m_bFirstFind = true;
        return;
    }

    nFindCount++;

    while (pEdit->findNext())
    {
        nFindCount++;
    }

    pEdit->execute(SCI_GOTOPOS, nBakCurrentPos);
    pEdit->execute(SCI_SETFIRSTVISIBLELINE, nBakFirstVisibleLine);
    pEdit->execute(SCI_SETXOFFSET, 0);

    // qDebug() << "Total occurrences found:" << nFindCount;
    // 直接弹出窗口提示
    QMessageBox::information(this, tr("Find"), tr("Total occurrences found: %1").arg(nFindCount));
}

void FindPage::__onClickedFindInCurFileButton()
{
    qDebug() << "__onClickedFindInCurFileButton()";
    QString findText = m_findTargetComboBox->currentText();
    if (findText.isEmpty())
    {
        return;
    }

    ScintillaEditView* pEdit = autoAdjustCurrentEditWin();
    if (pEdit == nullptr)
    {
        return;
    }

    updateParamsFromUI();

    FindRecords findRecords;
    findRecords.setEditView(pEdit);
    QString filepath = pEdit->property("FilePath").toString();
    findRecords.setFindFilePath(filepath);
    findRecords.setFindText(findText);

    int nBakCurrentPos = pEdit->execute(SCI_GETCURRENTPOS);
    int nBakFirstVisibleLine = pEdit->execute(SCI_GETFIRSTVISIBLELINE);

    // int nFindCount = 0;
    /// 从头开始查找
    bool bFind = pEdit->findFirst(findText, m_bRegularExpression, m_bMatchCase, m_bMatchWholeWord, false, true, 0, 0);
    if (!bFind)
    {
        m_bFirstFind = true;
        return;
    }

    FindRecord findRecord = getFindRecordFromLastFindState();
    findRecords.addFindRecord(findRecord);

    while (pEdit->findNext())
    {
        findRecord = getFindRecordFromLastFindState();
        findRecords.addFindRecord(findRecord);
    }

    pEdit->execute(SCI_GOTOPOS, nBakCurrentPos);
    pEdit->execute(SCI_SETFIRSTVISIBLELINE, nBakFirstVisibleLine);
    pEdit->execute(SCI_SETXOFFSET, 0);

    m_bFirstFind = true;

    // log findRecodes
    // QVector<FindRecord> findRecods = findRecords.getFindRecordList();
    // for (int i = 0; i < findRecods.size(); i++)
    // {
    //     FindRecord findRecord = findRecods[i];
    //     qDebug() << "line:" << findRecord.getLineNums() << "text:" << findRecord.getLineContents();
    // }
    // qDebug() << "emit showFindRecords";
    emit showFindRecords(&findRecords);
}

void FindPage::__onClickedClearButton()
{
    qDebug() << "__onClickedClearButton()";
}
