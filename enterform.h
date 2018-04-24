#ifndef ENTERFORM_H
#define ENTERFORM_H

#include <QWidget>

namespace Ui {
class EnterForm;
}

class EnterForm : public QWidget
{
    Q_OBJECT

public:
    explicit EnterForm(QWidget *parent = 0);
    ~EnterForm();

signals:
    void closed(int);

private slots:
    void on_adminButton_clicked();

    void on_UserButton_clicked();

private:
    Ui::EnterForm *ui;
};

#endif // ENTERFORM_H
