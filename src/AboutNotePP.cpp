#include "AboutNotePP.h"
#include "StyleSheetUtils.h"

AboutNotePP::AboutNotePP(QWidget *parent) : QDialog(parent)
{
    m_vMainLayout = new QVBoxLayout(this);
    m_titleLabel = new QLabel(tr("Simple Info For Notepad."), this);
    // 设置titleLabel的字体大小和加粗
    QFont titleFont = m_titleLabel->font();
    titleFont.setPointSize(12);
    titleFont.setBold(true);
    m_titleLabel->setFont(titleFont);

    m_versionKLabel = new QLabel(tr("Version:"), this);
    m_versionVLabel = new QLabel(tr("1.0.1"), this);
    m_contentKLabel = new QLabel(tr("Content:"), this);
    m_contentVLabel = new QLabel(tr("This is a simple notepad application."), this);

    auto hVerionLayout = new QHBoxLayout(this);
    hVerionLayout->addWidget(m_versionKLabel);
    hVerionLayout->addWidget(m_versionVLabel);
    hVerionLayout->addStretch();

    auto hContentLayout = new QHBoxLayout(this);
    hContentLayout->addWidget(m_contentKLabel);
    hContentLayout->addWidget(m_contentVLabel);
    hContentLayout->addStretch();

    m_vMainLayout->addSpacing(10);
    m_vMainLayout->addWidget(m_titleLabel);
    m_vMainLayout->addSpacing(25);
    m_vMainLayout->addLayout(hVerionLayout);
    m_vMainLayout->addSpacing(10);
    m_vMainLayout->addLayout(hContentLayout);

    setWindowTitle("NotepadPP");
    setFixedSize(300, 125);
    m_vMainLayout->setAlignment(Qt::AlignTop);
    m_vMainLayout->addStretch();
    setLayout(m_vMainLayout);

    StyleSheetUtils::setQssByFileName(this, ":/res/StyleSheet/AboutNotePP.qss");
}