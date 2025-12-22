#include "FindPage.h"
#include <QGroupBox>
#include <QDebug>
#include "ScintillaEditView.h"
#include <Qsci/qsciscintilla.h>

FindPage::FindPage(QWidget *parent) : QWidget(parent), m_editTabWidget(nullptr), m_sFindExpr(""), m_bReverseSearch(false),
    m_bMachWholeWord(false), m_bMachCase(false), m_bLoopSearch(false), m_bNormal(false), m_bExended(false), m_bRegularExpression(false),
    m_bFirstFind(true)
{
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
    m_countButton = new QPushButton(tr("Count"));
    m_countButton->setFixedWidth(150);
    m_vMainLayout->addWidget(m_countButton);
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
}

ScintillaEditView *FindPage::autoAdjustCurrentEditWin()
{
    // return nullptr;
    auto pEdit = dynamic_cast<ScintillaEditView*> (m_editTabWidget->currentWidget());
    if (pEdit == nullptr)
        return nullptr;

    if (pEdit != m_curEidtView)
    {
        m_bFirstFind = true;
        m_curEidtView = pEdit;
    }
    return pEdit;
}

void FindPage::setTabWidget(QTabWidget *tabWidget)
{
    m_editTabWidget = tabWidget;
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
    if (m_machWholeWordCheckBox->isChecked() != m_bMachWholeWord)
    {
        m_bMachWholeWord = m_machWholeWordCheckBox->isChecked();
        m_bFirstFind = true;
    }

    // 匹配大小写
    if (m_matchCaseCheckBox->isChecked() != m_bMachCase)
    {
        m_bMachCase = m_matchCaseCheckBox->isChecked();
        m_bFirstFind = true;
    }

    // 循环查找
    if (m_loopSearchCheckBox->isChecked() != m_bLoopSearch)
    {
        m_bLoopSearch = m_loopSearchCheckBox->isChecked();
        m_bFirstFind = true;
    }
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
        bool bFind = pEdit->findFirst(findText, m_bRegularExpression, m_bMachCase, m_bMachWholeWord, m_bLoopSearch, !m_bReverseSearch, -1, -1, true, false, false);
        if (!bFind)
        {
            qDebug() << "find failed";
            m_bFirstFind = true;
            return;
        }
        else
        {
            m_bFirstFind = false;

            // // FindState& findState = 
            // pEdit->getSelectionLinesRange
            // int nLine = 0;
            // int nIndexStart = 0;
            // int nIndexEnd = 0;
            // pEdit->lineIndexFromPosition();
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

}
