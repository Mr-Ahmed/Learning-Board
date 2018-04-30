#include "studentwidget.h"
#include "ui_studentwidget.h"

StudentWidget::StudentWidget(const StudentInformation& info, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentWidget)
{
    ui->setupUi(this);

    ui->IDLabel->setText(QString::number(info.id()));
    ui->NameLabel->setText(info.name());
    ui->CourseLabel->setText(info.course_name());

    QString scores;
    for(int i = 0; i < info.scores().size(); i++)
        scores += QString::number(info.scores()[i]) + " ";

    ui->Scores->setText(scores);
    ui->GPA->setText(QString::number(info.gpa()));
}

StudentWidget::~StudentWidget()
{
    delete ui;
}
