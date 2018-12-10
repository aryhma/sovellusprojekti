#include "pincodedialog.h"
#include "ui_pincodedialog.h"

PincodeDialog::PincodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PincodeDialog)
{
    ui->setupUi(this);

}

PincodeDialog::~PincodeDialog()
{
    delete ui;
}

void PincodeDialog::on_pushButton_clicked()
{
    emit receivedPIN(pin);

    this->close();
}

void PincodeDialog::on_btn1_clicked()
{
    pin +=ui->btn1->text();
}

void PincodeDialog::on_btn2_clicked()
{
     pin +=ui->btn2->text();
}

void PincodeDialog::on_btn3_clicked()
{
    pin +=ui->btn3->text();
}

void PincodeDialog::on_btn4_clicked()
{
    pin +=ui->btn4->text();
}

void PincodeDialog::on_btn5_clicked()
{
    pin +=ui->btn5->text();
}

void PincodeDialog::on_btn6_clicked()
{
    pin +=ui->btn6->text();
}

void PincodeDialog::on_btn7_clicked()
{
    pin +=ui->btn7->text();
}

void PincodeDialog::on_btn8_clicked()
{
    pin +=ui->btn8->text();
}

void PincodeDialog::on_btn9_clicked()
{
    pin +=ui->btn9->text();
}
