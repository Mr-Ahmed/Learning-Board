#ifndef ADDWIDGET_H
#define ADDWIDGET_H

#include <QWidget>
#include "studentinformation.h"

namespace Ui {
class AddWidget;
}

class AddWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddWidget(QWidget *parent = 0);
    ~AddWidget();

    // gettters for data from lineeditors
    QString getCourse() const;
    QString getName() const;
    quint32  getID() const;
    QVector<quint32> getScores() const;
    // give opportunities for changing button name
    void changeButtonName(const QString&);
    QString getButtonName() const;
    // set field form Student information
    void setField(const StudentInformation& info);

    // clear all field
    void clearField();

signals:
    // when the button click
    void closed();

private slots:
    void on_AddButton_clicked();

private:
    Ui::AddWidget *ui;
};

#endif // ADDWIDGET_H
