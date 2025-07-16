#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class NotePad;
}
QT_END_NAMESPACE

class NotePad : public QMainWindow
{
    Q_OBJECT

public:
    NotePad(QWidget *parent = nullptr);
    ~NotePad();

    void __conected();

private slots:
    void onActionNewToggled(bool check);

private:
    Ui::NotePad *ui;
};