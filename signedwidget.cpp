#include "signedwidget.h"
#include "ui_signedwidget.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDebug>

SignedWidget::SignedWidget(QWidget *parent) :
    QWidget(parent), m_type(-1),
    ui(new Ui::SignedWidget)
{
    ui->setupUi(this);
    ui->SignIn->setChecked(true);
    this->setWindowTitle("Logging");
    QRegExp regID("^[0-9]{5,}$");

    ui->LoginLine->setValidator(new QRegExpValidator(regID));
    connect(ui->enterButton, SIGNAL(clicked(bool)), SLOT(doAction()));


}

void SignedWidget::show(int type)
{
    m_type = type;
    QWidget::show();
}

SignedWidget::~SignedWidget()
{
    delete ui;
}

void SignedWidget::doAction()
{
    qDebug() << m_type;
    ui->ErrorLine->clear();

    if(!QDir().exists(mode[m_type]))
        QDir().mkdir(mode[m_type]);

    QString path = mode[m_type];
    path += "/" + ui->LoginLine->text() + ".txt";

    qDebug() << path;

    QFile file(path);

    if(ui->LogIn->isChecked())
    {
        if(!file.exists())
        {
            ui->ErrorLine->setText("<FONT COLOR=#CC0033>The user with given login is not exist</FONT>");
            return;
        }
        else
        {
            file.open(QFile::ReadOnly);
            QString pass = file.readAll();
            QString inputPass = ui->PassworLine->text();

            if(pass != inputPass)
            {
                 ui->ErrorLine->setText("<FONT COLOR=#008000>Incorrect password</FONT>");
                 return;
            }
            else
            {
                qDebug() << m_type;
                emit logged(m_type, ui->LoginLine->text().toInt());
                this->close();
            }
        }
    }
    else
    {
        qDebug() << m_type;
        if(file.exists())
        {
            ui->ErrorLine->setText("<FONT COLOR=#CC0033>The user with given login is already exist</FONT>");
            return;
        }
        else
        {
            file.open(QFile::WriteOnly);
            qDebug() << path;
            QTextStream strm(&file);
            strm << ui->PassworLine->text();

            ui->ErrorLine->setText("Re-enter the password");
            ui->LogIn->setChecked(true);
            ui->SignIn->hide();
            ui->LogIn->hide();
            ui->PassworLine->clear();

        }
    }
}
