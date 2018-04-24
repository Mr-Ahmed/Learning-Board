#include "actionwidget.h"
#include "ui_actionwidget.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QRegularExpression>
#include <algorithm>
#include <QCloseEvent>
#include <QDebug>
#include <QMessageBox>

AddWidget::AddWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddWidget)
{
    ui->setupUi(this);
    // validator for some line editors
    QRegExp regID("^[0-9]{5,}$");
    QRegExp regScores("([0-9]{1,3}[ ]){0,}");

    ui->IDLine->setValidator(new QRegExpValidator(regID, this));
    ui->ScoresLine->setValidator(new QRegExpValidator(regScores, this));

    setWindowTitle("Action");

}

AddWidget::~AddWidget()
{
    delete ui;
}

QString AddWidget::getCourse() const
{
    return ui->CourseLine->text();
}

QString AddWidget::getName() const
{
    return ui->lineEdit->text();
}

quint32 AddWidget::getID() const
{
    return ui->IDLine->text().toInt();
}

QVector<quint32> AddWidget::getScores() const
{
    QString scorestext = ui->ScoresLine->text();
    if(!scorestext.isEmpty() && scorestext.endsWith(" "))
        scorestext.remove(scorestext.size()-1, 1);
    QStringList lst = scorestext.split(' ');

    QVector<quint32> scores;
    scores.resize(lst.size());

    std::transform(lst.begin(), lst.end(), scores.begin(), [](const QString& str)
    {
        return str.toInt();
    });
    return scores;

}

void AddWidget::changeButtonName(const QString &name)
{
    ui->AddButton->setText(name);
}

QString AddWidget::getButtonName() const
{
    return ui->AddButton->text();
}

void AddWidget::setField(const StudentInformation &info)
{
    // initalize the all field of widget from info
    ui->CourseLine->setText(info.course_name());
    ui->IDLine->setText(QString::number(info.id()));
    ui->lineEdit->setText(info.name());

    QStringList text;

    auto scores = info.scores();
    std::transform(scores.begin(), scores.end(), std::back_inserter(text), [](quint32 n)
    {
        return QString::number(n);
    });

    ui->ScoresLine->setText(text.join(' '));


}

// clear all text field
void AddWidget::clearField()
{
    ui->CourseLine->clear();
    ui->IDLine->clear();
    ui->lineEdit->clear();
    ui->ScoresLine->clear();
}



void AddWidget::on_AddButton_clicked()
{
    // if all line filled
    if(!ui->CourseLine->text().isEmpty() && !ui->IDLine->text().isEmpty()
            && !ui->lineEdit->text().isEmpty())
    {
        emit closed();
        this->close();
    }
    // otherwise display message
    else
    {

        QMessageBox::information(nullptr, "Data field",
                                 "Data fields are not filled",
                                 QMessageBox::Ok);
    }

}
