#include "ReplacePage.h"
#include <QGroupBox>
#include <QDebug>
#include "ScintillaEditView.h"


ReplacePage::ReplacePage(QWidget *parent) : QWidget(parent),
    m_editTabWidget(nullptr),
    m_sFindExpr(""),
    m_sReplaceExpr(""),
    m_bReverseSearch(false),
    m_bMatchWholeWord(false),
    m_bMatchCase(false),
    m_bLoopSearch(false),
    m_bRegularExpression(false),
    m_bFirstFind(true),
    m_curEditView(nullptr),
    m_lastClickedButtonType(LastClickedButtonType::ReplaceNext)
{
    __initUI();
    __connect();
}

void ReplacePage::__initUI()
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

    auto hReplaceTargetLayout = new QHBoxLayout();
    m_replaceTargetLabel = new QLabel(tr("Replace Target:"));
    m_replaceTargetLabel->setFixedWidth(120);
    m_replaceTargetComboBox = new QComboBox();
    m_replaceTargetComboBox->setEditable(true);
    hReplaceTargetLayout->addWidget(m_replaceTargetLabel);
    hReplaceTargetLayout->addWidget(m_replaceTargetComboBox, 1);
    m_vMainLayout->addLayout(hReplaceTargetLayout);

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
    m_replaceNextButton = new QPushButton(tr("Replace Next"));
    m_replaceNextButton->setFixedWidth(150);
    m_vMainLayout->addWidget(m_replaceNextButton);
    // 查找上一个
    m_replacePrevButton = new QPushButton(tr("Replace Prev"));
    m_replacePrevButton->setFixedWidth(150);
    m_vMainLayout->addWidget(m_replacePrevButton);


    // 在文件中查找
    m_replaceInCurFileButton = new QPushButton(tr("Replace In Current File"));
    m_replaceInCurFileButton->setFixedWidth(150);
    m_vMainLayout->addWidget(m_replaceInCurFileButton);

    // 查找所有打开文件
    m_replaceInAllFileButton = new QPushButton(tr("Replace In All Open Files"));
    m_replaceInAllFileButton->setFixedWidth(150);
    m_vMainLayout->addWidget(m_replaceInAllFileButton);

    m_vMainLayout->addStretch();
}

void ReplacePage::__connect()
{
    connect(m_replaceNextButton, &QPushButton::clicked, this, &ReplacePage::__onClickedReplaceNextButton);
    connect(m_replacePrevButton, &QPushButton::clicked, this, &ReplacePage::__onClickedReplacePrevButton);
    connect(m_replaceInCurFileButton, &QPushButton::clicked, this, &ReplacePage::__onClickedReplaceInCurFileButton);
    connect(m_replaceInAllFileButton, &QPushButton::clicked, this, &ReplacePage::__onClickedReplaceInAllFileButton);
}

ScintillaEditView *ReplacePage::autoAdjustCurrentEditWin()
{
    auto pEdit = dynamic_cast<ScintillaEditView*>(m_editTabWidget->currentWidget());
    if (pEdit == nullptr)
    {
        return pEdit;
    }

    if (pEdit != m_curEditView)
    {
        m_bFirstFind = true;
        m_curEditView = pEdit;
    }
    return pEdit;
}

void ReplacePage::setTabWidget(QTabWidget *tabWidget)
{
    m_editTabWidget = tabWidget;
}

void ReplacePage::setNoteWidget(QWidget *pNoteWidget)
{
    m_pNotepadWidget = pNoteWidget;
}

void ReplacePage::updateParamsFromUI()
{
    if (m_findTargetComboBox->currentText() != m_sFindExpr)
    {
        m_sFindExpr = m_findTargetComboBox->currentText();
        m_bFirstFind = true;
    }

    if (m_replaceTargetComboBox->currentText() != m_sReplaceExpr)
    {
        m_sReplaceExpr = m_replaceTargetComboBox->currentText();
        m_bFirstFind = true;
    }

    if (m_regexRadioButton->isChecked() != m_bRegularExpression)
    {
        m_bRegularExpression = m_regexRadioButton->isChecked();
        m_bFirstFind = true;
    }


    if (m_reverseSearchCheckBox->isChecked() != m_bReverseSearch)
    {
        m_bReverseSearch = m_regexRadioButton->isChecked();
        m_bFirstFind = true;
    }

    if (m_machWholeWordCheckBox->isChecked() != m_bMatchWholeWord)
    {
        m_bMatchWholeWord = m_machWholeWordCheckBox->isChecked();
        m_bFirstFind = true;
    }

    if (m_matchCaseCheckBox->isChecked() != m_bMatchCase)
    {
        m_bMatchCase = m_matchCaseCheckBox->isChecked();
        m_bFirstFind = true;
    }

    if (m_loopSearchCheckBox->isChecked() != m_bLoopSearch)
    {
        m_bLoopSearch = m_loopSearchCheckBox->isChecked();
        m_bFirstFind = true;
    }
}

void ReplacePage::__onClickedReplaceNextButton()
{
    qDebug() << "ReplacePage::__onClickedReplaceNextButton()";
    if (m_findTargetComboBox->currentText().isEmpty())
    {
        qDebug() << "find target is empty";
        return;
    }

    // if (m_replaceTargetComboBox->currentText().isEmpty())
    // {
    //     qDebug() << "replace target is empty";
    //     return;
    // }
    
    ScintillaEditView* pEdit = autoAdjustCurrentEditWin();
    updateParamsFromUI();

    if (m_lastClickedButtonType == LastClickedButtonType::ReplacePrev)
    {
        m_bFirstFind = true;
    }

    if (m_bFirstFind)
    {
        bool bFind = pEdit->findFirst(m_sFindExpr, m_bRegularExpression, m_bMatchCase, m_bMatchWholeWord, m_bLoopSearch, !m_bReverseSearch, -1, -1, true, false, false);
        if (!bFind)
        {
            qDebug() << "find failed";
            m_bFirstFind = true;
            // return;
        }
        else
        {
            // pEdit->replace(m_sReplaceExpr);
            m_bFirstFind = false;
        }
    }
    else
    {
        pEdit->replace(m_sReplaceExpr);
        bool bFind = pEdit->findNext();
        if (!bFind)
        {
            qDebug() << "Not found";
        }
        // else
        // {
            // pEdit->replace(m_sReplaceExpr);
        // }
    }
    m_lastClickedButtonType = LastClickedButtonType::ReplaceNext;
}

void ReplacePage::__onClickedReplacePrevButton()
{
    qDebug() << "ReplacePage::__onClickedReplacePrevButton()";
    if (m_findTargetComboBox->currentText().isEmpty())
    {
        qDebug() << "find target is empty";
        return;
    }

    ScintillaEditView* pEdit = autoAdjustCurrentEditWin();
    updateParamsFromUI();
    bool bForward = !m_bReverseSearch;
    if (m_lastClickedButtonType == LastClickedButtonType::ReplaceNext)
    {
        bForward = !bForward;
        m_bFirstFind = true;
    }

    if (m_bFirstFind)
    {
        bool bFind = pEdit->findFirst(m_sFindExpr, m_bRegularExpression, m_bMatchCase, m_bMatchWholeWord, m_bLoopSearch, bForward, -1, -1, true, false, false);
        if (!bFind)
        {
            qDebug() << "find failed";
            m_bFirstFind = true;
            // return;
        }
        else
        {
            m_bFirstFind = false;
        }
    }
    else
    {
        pEdit->replace(m_sReplaceExpr);
        bool bFind = pEdit->findNext();
        if (!bFind)
        {
            qDebug() << "Not found";
        }
    }

    m_lastClickedButtonType = LastClickedButtonType::ReplacePrev;


}

void ReplacePage::__onClickedReplaceInCurFileButton()
{
    qDebug() << "ReplacePage::__onClickedReplaceInCurFileButton()";
}

void ReplacePage::__onClickedReplaceInAllFileButton()
{
    qDebug() << "ReplacePage::__onClickedReplaceInAllFileButton()";
}
