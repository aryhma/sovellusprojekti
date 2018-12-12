#include "lahjoita.h"
#include "ui_lahjoita.h"

Lahjoita::Lahjoita(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Lahjoita)
{
    ui->setupUi(this);
}

Lahjoita::~Lahjoita()
{
    delete ui;
}
