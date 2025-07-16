#include "notepad.h"
#include "./ui_notepad.h"
#include <QDebug>

NotePad::NotePad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::NotePad)
{
    ui->setupUi(this);

    __conected();
}

NotePad::~NotePad()
{
    delete ui;
}

void NotePad::__conected()
{
    connect(ui->actionNew, &QAction::triggered, this, &NotePad::onActionNewToggled);
}

void NotePad::onActionNewToggled(bool check)
{
    qDebug() << "clicked action new";
}

