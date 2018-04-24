#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "datastorage.h"
#include <QWidget>

namespace Ui {
class MainWidget;
}

class AddWidget;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);

    ~MainWidget();

private slots:
    // different reaction on the button clicked
    void on_removeButton_clicked();
    void on_addButton_clicked();

    // add/changing selected rows
    void addRow();
    void changeRow();

    void on_changeButton_clicked();

public slots:
    // display this widget in some mode
    void show(int type);

private:
    //fill table from file
    void fillTable();

    // add the data info
    void addRowWith(const StudentInformation& info);


private:
    Ui::MainWidget *ui;
    DataStorage store;
    AddWidget* addwidget = nullptr;
    int changeIndex = -1;
};

#endif // MAINWIDGET_H
