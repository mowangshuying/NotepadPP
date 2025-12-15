#include "StyleSheetUtils.h"
#include <QDebug>
#include <QFile>

QString StyleSheetUtils::getQssByFileName(QString fileName)
{
    // return QString();.
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        QString qssStr = file.readAll();
        file.close();
        return qssStr;
    }
    return "";
}

void StyleSheetUtils::setQssByFileName(QWidget *pWidget, QString fileName)
{
    QString qss = StyleSheetUtils::getQssByFileName(fileName);
    pWidget->setStyleSheet(qss);
}
