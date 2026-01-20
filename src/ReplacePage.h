#pragma once

#include <QWidget>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QVBoxLayout>

class ReplacePage : public QWidget
{
    Q_OBJECT
  public:
    ReplacePage(QWidget* parent = nullptr);

    void __initUI();

    void __connect();

    void setNoteWidget(QWidget* pNoteWidget);
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

    QWidget* m_pNotepadWidget;
};