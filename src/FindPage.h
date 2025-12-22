#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QTabWidget>


class ScintillaEditView;
class FindPage : public QWidget
{ 
    Q_OBJECT
public:
    FindPage(QWidget *parent = nullptr);

    void __initUI();
    void __connect();

    ScintillaEditView* autoAdjustCurrentEditWin();

    void setTabWidget(QTabWidget* tabWidget);

    void updateParamsFromUI();

    // slots;
    void __onClickedFindNextButton();
protected:

//// ui;
    QVBoxLayout* m_vMainLayout;
    QLabel* m_findTargetLabel;
    QComboBox* m_findTargetComboBox;

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

    // 查找下一个
    QPushButton* m_findNextButton;
    // 查找上一个
    QPushButton* m_findPrevButton;
    // 计数
    QPushButton* m_countButton;
    // 在当前文件中查找
    QPushButton* m_findInCurFileButton;
    // 在所有打开文件中查找
    QPushButton* m_findInAllFileButton;
    // 清空
    QPushButton* m_clearButton;

//// var;
    QTabWidget* m_editTabWidget;
    ScintillaEditView* m_curEidtView;

    QString m_sFindExpr; // 表达式
    bool m_bReverseSearch; // 反向查找
    bool m_bMachWholeWord; // 全字匹配
    bool m_bMachCase; // 匹配大小写
    bool m_bLoopSearch; // 循环查找
    bool m_bNormal;
    bool m_bExended; // 扩展
    bool m_bRegularExpression; // 正则表达式

    bool m_bFirstFind;
};