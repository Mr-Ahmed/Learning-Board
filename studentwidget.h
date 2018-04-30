#ifndef STUDENTWIDGET_H
#define STUDENTWIDGET_H

#include <QWidget>
#include "studentinformation.h"

namespace Ui {
class StudentWidget;
}

class StudentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StudentWidget(const StudentInformation& info,QWidget *parent = 0);
    ~StudentWidget();

private:
    Ui::StudentWidget *ui;
};

#endif // STUDENTWIDGET_H
