#include "AboutNotePP.h"
#include "StyleSheetUtils.h"

AboutNotePP::AboutNotePP(QWidget *parent) : QDialog(parent)
{
    m_vMainLayout = new QVBoxLayout(this);

    QFont versionFont = QFont();
    versionFont.setPointSize(12);
    versionFont.setBold(true);

    QFont contentFont = QFont();
    contentFont.setPointSize(10);

    m_versionLabel = new QLabel(tr("NotePadPP 1.0.2"), this);
    QFont font = m_versionLabel->font();
    font.setPointSize(12);
    font.setBold(true);
    m_versionLabel->setFont(versionFont);

    m_copyrightLabel = new QLabel(tr("Copyright (C) 2025-2026 NotepadPP"), this);
    m_copyrightLabel->setFont(contentFont);
    m_contentLabel = new QLabel(tr("This program is free software: you can redistribute it and/or modify"
        "it underthetermsoftheGNuGeneralPublicLicenseaspublished"
        "by the Free Software Foundation, either version 3 of the License,or"
        "(at your option) any later version."
        "This programis distributed in thehope that it willbe useful,but"
        "WITHOUT ANY WARRANTY; without even the implied warranty of"
        "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See"
        "the GNU General Public License for more details."
        "You should have received a copy of the GNU General Public License"
        "along with this program. If not, see <https://www.gnu.org/licenses/"), this);
    m_contentLabel->setFont(contentFont);
    m_contentLabel->setWordWrap(true);

    m_vMainLayout->addWidget(m_versionLabel);
    m_vMainLayout->addWidget(m_copyrightLabel);
    m_vMainLayout->addWidget(m_contentLabel);

    setWindowTitle("NotepadPP");
    setFixedSize(500, 215);
    m_vMainLayout->setAlignment(Qt::AlignTop);
    m_vMainLayout->addStretch();
    setLayout(m_vMainLayout);
}