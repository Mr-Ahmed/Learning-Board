#include "enterform.h"
#include "ui_enterform.h"

EnterForm::EnterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnterForm)
{
    ui->setupUi(this);
    setWindowTitle("LMS");

}

EnterForm::~EnterForm()
{
    delete ui;
}

void EnterForm::on_adminButton_clicked()
{
    emit closed(0);
    close();
}


void EnterForm::on_UserButton_clicked()
{
    emit closed(1);
    close();
}
