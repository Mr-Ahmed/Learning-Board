#ifndef SIGNEDWIDGET_H
#define SIGNEDWIDGET_H

#include <QWidget>
#include <QString>

namespace Ui {
class SignedWidget;
}

class SignedWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SignedWidget(QWidget *parent = 0);

    ~SignedWidget();

signals:
    void logged(int,int);

public slots:
    void show(int type);

private slots:
    void doAction();

private:
    Ui::SignedWidget *ui;
    int m_type;

    const QString mode[2] = {"Admin", "User"};
};

#endif // SIGNEDWIDGET_H
