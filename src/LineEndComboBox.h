#pragma once

#include <QcomboBox>
#include "StyleSheetUtils.h"

class LineEndComboBox : public QComboBox
{
    Q_OBJECT
public:
    LineEndComboBox(QWidget* parent = nullptr)
    {
        StyleSheetUtils::setQssByFileName(this, "./res/StyleSheet/LineEndComboBox.qss");
    }
};