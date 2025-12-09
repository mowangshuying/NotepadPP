#include "AboutNotePP.h"

AboutNotePP::AboutNotePP(QWidget *parent) : QDialog(parent)
{
    m_vMainLayout = new QVBoxLayout(this);
    m_titleLabel = new QLabel("Simple Info For Notepad.", this);
    // 设置titleLabel的字体大小和加粗
    QFont titleFont = m_titleLabel->font();
    titleFont.setPointSize(12);
    titleFont.setBold(true);
    m_titleLabel->setFont(titleFont);

    m_versionKLabel = new QLabel("Version:", this);
    // m_versionKLabel->setAlignment(Qt::AlignLeft);
    m_versionVLabel = new QLabel("1.0.0", this);
    // m_versionVLabel->setAlignment(Qt::AlignLeft);
    m_contentKLabel = new QLabel("Content:", this);
    // m_contentKLabel->setAlignment(Qt::AlignLeft);
    m_contentVLabel = new QLabel("This is a simple notepad application.", this);
    // m_contentVLabel->setAlignment(Qt::AlignLeft);

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
}