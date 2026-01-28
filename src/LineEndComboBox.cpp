#include "LineEndComboBox.h"

LineEndComboBox::LineEndComboBox(QWidget* parent /*= nullptr*/) : QComboBox(parent)
{
    StyleSheetUtils::setQssByFileName(this, ":/res/StyleSheet/LineEndComboBox.qss");
}
