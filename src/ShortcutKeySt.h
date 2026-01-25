#pragma once

#include <QString>
#include <QKeySequence>

class ShortcutKeySt
{
  public:
    ShortcutKeySt(QString name, QString iniTag, QKeySequence shortcut, bool bCanModify = true) : m_iniTag(iniTag), m_name(name), m_bCanModify(bCanModify)
    {
        m_shortcut = QKeySequence(shortcut);
    }

    void setIniTag(QString iniTag)
    {
        m_iniTag = iniTag;
    }

    QString getIniTag()
    {
        return m_iniTag;
    }

    void setName(QString name)
    {
        m_name = name;
    }

    QString getName()
    {
        return m_name;
    }

    void setShortcut(QKeySequence shortcut)
    {
        m_shortcut = shortcut;
    }

    QKeySequence getShortcut()
    {
        return m_shortcut;
    }

    void setCanModify(bool bCanModify)
    {
        m_bCanModify = bCanModify;
    }

    bool getCanModify()
    {
        return m_bCanModify;
    }

  protected:
    QString m_iniTag;
    QString m_name;
    QKeySequence m_shortcut;
    bool m_bCanModify;
};

using ShortcutKeyStVct = std::vector<ShortcutKeySt>;