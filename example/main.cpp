#include <QApplication>
#include <QWidget>

int main(int argc, char** argv)
{
    QAPplication app(argc, argv);

    QWidget w;
    w.show();

    return app.exec();
}