#pragma once

#include <QObject>
#include <QSettings>

class ConfigUtils : public QObject
{
    Q_OBJECT
  public:
    ConfigUtils();
    ~ConfigUtils();

    static ConfigUtils* getUtils();

    void setLanguage(QString language);
    QString getLanguage();

  protected:
    QSettings* m_settings;
};