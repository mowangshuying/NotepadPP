#pragma once

#include <QStyledItemDelegate>
#include <QPainter>

class HtmlStyledItemDelegate : public QStyledItemDelegate
{
  public:
    Q_OBJECT

  public:
    HtmlStyledItemDelegate(QObject *parent = nullptr);

    void setFontSize(int fontSize);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

  protected:
    int m_defaultFontSize;
};