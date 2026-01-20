#pragma once

#include <QWidget>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QVBoxLayout>

class ScintillaEditView;
class ReplacePage : public QWidget
{
    Q_OBJECT
  public:
    enum class LastClickedButtonType
    {
        ReplaceNext,
        ReplacePrev,
        ReplaceInCurFile,
        ReplaceInAllFile
    };
  public:
    ReplacePage(QWidget* parent = nullptr);

    void __initUI();

    void __connect();

    ScintillaEditView* autoAdjustCurrentEditWin();

    void setTabWidget(QTabWidget* tabWidget);
    void setNoteWidget(QWidget* pNoteWidget);

    void updateParamsFromUI();
  // signals:
  // public slots:
    void __onClickedReplaceNextButton();
    void __onClickedReplacePrevButton();
    void __onClickedReplaceInCurFileButton();
    void __onClickedReplaceInAllFileButton();
  protected:
    QVBoxLayout* m_vMainLayout;
    QLabel* m_findTargetLabel;
    QComboBox* m_findTargetComboBox;

    QLabel* m_replaceTargetLabel;
    QComboBox* m_replaceTargetComboBox;

    // 反向查找
    QCheckBox* m_reverseSearchCheckBox;
    // 全词匹配
    QCheckBox* m_machWholeWordCheckBox;
    // 匹配大小写
    QCheckBox* m_matchCaseCheckBox;
    // 循环查找
    QCheckBox* m_loopSearchCheckBox;

    // 普通
    QRadioButton* m_normalRadioButton;
    // 扩展
    QRadioButton* m_extendedRadioButton;
    // 正则表达式
    QRadioButton* m_regexRadioButton;

    // 替换下一个
    QPushButton* m_replaceNextButton;
    // 替换上一个
    QPushButton* m_replacePrevButton;

    // 在当前文件中替换
    QPushButton* m_replaceInCurFileButton;
    
    // 在所有打开文件中替换
    QPushButton* m_replaceInAllFileButton;


    /// var;
    QTabWidget* m_editTabWidget;
    ScintillaEditView* m_curEditView;

    //
    QString m_sFindExpr; // 表达式
    QString m_sReplaceExpr;
    bool m_bReverseSearch; // 反向查找
    bool m_bMatchWholeWord; // 全字匹配
    bool m_bMatchCase; // 匹配大小写
    bool m_bLoopSearch; // 循环查找
    bool m_bNormal; 
    bool m_bExended;  //扩展
    bool m_bRegularExpression; // 正则表达式

    bool m_bFirstFind;
    LastClickedButtonType m_lastClickedButtonType;
    QWidget* m_pNotepadWidget;
};