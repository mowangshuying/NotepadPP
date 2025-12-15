#pragma once

#include <QWidget>
#include <QString>

class StyleSheetUtils : public QObject
{
public:
    static QString getQssByFileName(QString fileName);
    static void setQssByFileName(QWidget* pWidget, QString fileName);
};