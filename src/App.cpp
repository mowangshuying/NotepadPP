#include <QApplication>
#include <QWidget>

#include "NotepadPP.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    NotepadPP pp;
    pp.show();

    return app.exec();
}