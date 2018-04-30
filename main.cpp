#include "mainwidget.h"
#include "enterform.h"
#include "signedwidget.h"
#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    SignedWidget widget;
    EnterForm form;
    MainWidget mwdgt;
    form.show();

    QObject::connect(&form, SIGNAL(closed(int)), &widget, SLOT(show(int)));
    QObject::connect(&widget, SIGNAL(logged(int, int)), &mwdgt, SLOT(show(int, int)));

    return a.exec();
}
