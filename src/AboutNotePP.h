#pragma once

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

class AboutNotePP : public QDialog
{
    Q_OBJECT
  public:
    AboutNotePP(QWidget* parent = nullptr);

  protected:
    QVBoxLayout* m_vMainLayout;
    QLabel* m_titleLabel;

    QLabel* m_versionKLabel;
    QLabel* m_versionVLabel;

    QLabel* m_contentKLabel;
    QLabel* m_contentVLabel;
};