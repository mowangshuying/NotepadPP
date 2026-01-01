#include <QApplication>
#include <QWidget>
#include <QTranslator>

#include "NotepadPP.h"
#include "ConfigUtils.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QTranslator translator;
    if (ConfigUtils::getUtils()->getLanguage() == "zh-CN")
    {
        bool bLoad = translator.load("./res/i18n/zh-CN.qm");
        if (bLoad)
        {
            app.installTranslator(&translator);
        }
    }
    else if (ConfigUtils::getUtils()->getLanguage() == "en-US")
    {
        bool bLoad = translator.load("./res/i18n/en-US.qm");
        if (bLoad)
        {
            app.installTranslator(&translator);
        }
    }


    NotepadPP pp;
    pp.show();

    return app.exec();
}