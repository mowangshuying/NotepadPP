#include "ConfigUtils.h"

ConfigUtils::ConfigUtils()
{
    m_settings = new QSettings("../config/config.ini", QSettings::IniFormat);
}

ConfigUtils::~ConfigUtils()
{
    delete m_settings;
}

ConfigUtils* ConfigUtils::getUtils()
{
    // return nullptr;
    static ConfigUtils utils;
    return &utils;
}

void ConfigUtils::setLanguage(QString language)
{
    m_settings->beginGroup("config");
    m_settings->setValue("language", language);
    m_settings->endGroup();
}

QString ConfigUtils::getLanguage()
{
    // return QString();
    m_settings->beginGroup("config");
    QString languageStr = m_settings->value("language", "en-US").toString();
    m_settings->endGroup();
    return languageStr;
}
