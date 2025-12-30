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
};