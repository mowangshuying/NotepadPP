#include "HtmlStyledItemDelegate.h"
#include <QApplication>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>

HtmlStyledItemDelegate::HtmlStyledItemDelegate(QObject *parent) : QStyledItemDelegate(parent), m_defaultFontSize(14)
{
}

void HtmlStyledItemDelegate::setFontSize(int fontSize)
{
    m_defaultFontSize = fontSize;
}

void HtmlStyledItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);

    QStyle* style = opt.widget ? opt.widget->style() : QApplication::style();

    QString text = opt.text;
    opt.text.clear();

    // 将opt.txt清空后首次绘制
    style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, opt.widget);

    QTextDocument doc;
    doc.setHtml(text);

    QAbstractTextDocumentLayout::PaintContext ctx;
    QRect textRect = style->subElementRect(QStyle::SE_ItemViewItemText, &opt);

    painter->save();
    painter->translate(textRect.topLeft());
    painter->setClipRect(textRect.translated(-textRect.topLeft()));
    doc.documentLayout()->draw(painter, ctx);
    painter->restore();
}
