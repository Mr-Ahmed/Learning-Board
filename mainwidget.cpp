#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QMessageBox>
#include "actionwidget.h"
#include <iterator>
#include <QDebug>
#include "studentwidget.h"


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    this->setFixedSize(QSize{880,480});

    // if can't loaded data, display message
    if(!store.loadFromFile(FILENAME))
    {
        QMessageBox::warning(nullptr, "Data loads",
                             "The data did not load properly", QMessageBox::Ok);
    }

    // set the header of tablewidget
    QStringList lstHeader;
    lstHeader << "ID" << "NAME" << "COURSE" << "SCORES" << "GPA";
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(lstHeader);
    ui->tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

    setWindowTitle("LMS");

    // fill table from file
    fillTable();


}

//depends on the type display the main widget
void MainWidget::show(int type, int id)
{
    if(type == 1)
    {
        for(int i = 0; i < store.size(); i++)
        {
            if(store[i].id() == id)
            {
                (new StudentWidget(store[i]))->show();
                return;
            }
        }

        QMessageBox::warning(0, "Student", "The student with given ID is not exist in database");

    }
    else QWidget::show();

}

MainWidget::~MainWidget()
{
    // save the file and delete widgets
    store.saveToFile(FILENAME);
    delete addwidget;
    delete ui;

}

void MainWidget::on_removeButton_clicked()
{
    // get selected items
    int rowidx = ui->tableWidget->currentRow();
    // remove the selected item

    if(rowidx != -1)
    {
        ui->tableWidget->removeRow(rowidx);
        store.remove(rowidx);
    }


}

void MainWidget::on_addButton_clicked()
{
    // some magic with connect()
    if(!addwidget){
        addwidget = new ActionWidget();
        addwidget->changeButtonName("Add");
        connect(addwidget, SIGNAL(closed()), this, SLOT(addRow()));
    }

    disconnect(addwidget, SIGNAL(closed()), this, SLOT(changeRow()));
    if(addwidget->getButtonName() != "Add")
    {
        addwidget->changeButtonName("Add");
       connect(addwidget, SIGNAL(closed()), this, SLOT(addRow()));
    }

    // clear field and display window
    addwidget->clearField();
    addwidget->show();
}

void MainWidget::addRow()
{
    // add row
    StudentInformation info;
    info.setScores(addwidget->getScores());
    info.setId(addwidget->getID());
    info.setName(addwidget->getName());
    info.setCourse_name(addwidget->getCourse());
    info.calculateGPA();
    store.add(info);

    addRowWith(info);

}

void MainWidget::changeRow()
{
    if(changeIndex != -1)
    {
        // if the index of chaged row is valid
        StudentInformation info;
        info.setScores(addwidget->getScores());
        info.setId(addwidget->getID());
        info.setName(addwidget->getName());
        info.setCourse_name(addwidget->getCourse());
        info.calculateGPA();
        store[changeIndex] = info;

        // changing the context of tablewidget
        ui->tableWidget->item(changeIndex,0)->setText(QString::number(info.id()));
        ui->tableWidget->item(changeIndex,1)->setText(info.name());
        ui->tableWidget->item(changeIndex,2)->setText(info.course_name());
        auto scores = info.scores();

        // if the changes index is emty
        if(scores.size() == 1 && scores[0] == 0){
            ui->tableWidget->item(changeIndex, 3)->setText("");
            ui->tableWidget->item(changeIndex, 4)->setText("0.00");
            return;
        }

        QStringList text;

        std::transform(scores.begin(), scores.end(), std::back_inserter(text), [](quint32 n)
        {
            return QString::number(n);
        });


        ui->tableWidget->item(changeIndex, 3)->setText(text.join(' '));
        ui->tableWidget->item(changeIndex, 4)->setText(QString::number(info.gpa(), 'f', 2));
    }
}

void MainWidget::fillTable()
{
    for(size_t i = 0; i < store.size(); i++)
        addRowWith(store[i]);

}

void MainWidget::addRowWith(const StudentInformation &info)
{
    // create new QTableWidget Item and insert it into table
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    int rowsIdx = ui->tableWidget->rowCount()-1;
    ui->tableWidget->setItem(rowsIdx,0, new QTableWidgetItem(QString::number(info.id())));
    ui->tableWidget->setItem(rowsIdx,1, new QTableWidgetItem(info.name()));
    ui->tableWidget->setItem(rowsIdx,2, new QTableWidgetItem(info.course_name()));
    auto scores = info.scores();


    if(scores.size() == 1 && scores[0] == 0){
        ui->tableWidget->setItem(rowsIdx, 3, new QTableWidgetItem(""));
        return;
    }

    QStringList text;

    std::transform(scores.begin(), scores.end(), std::back_inserter(text), [](quint32 n)
    {
        return QString::number(n);
    });
    ui->tableWidget->setItem(rowsIdx, 3, new QTableWidgetItem(text.join(' ')));
    ui->tableWidget->setItem(rowsIdx, 4, new QTableWidgetItem(QString::number(info.gpa(), 'f', 2)));
}

void MainWidget::on_changeButton_clicked()
{
    int rowIdx = ui->tableWidget->currentRow();
    if(rowIdx == -1) return ;

    changeIndex = rowIdx;

    if(!addwidget)
    {
        addwidget = new ActionWidget();
        addwidget->changeButtonName("Change");
        connect(addwidget, SIGNAL(closed()), this, SLOT(changeRow()));
    }
    else
    {
        disconnect(addwidget, SIGNAL(closed()), this, SLOT(addRow()));
        if(addwidget->getButtonName() != "Change")
        {
            connect(addwidget, SIGNAL(closed()), this, SLOT(changeRow()));

        }
        addwidget->clearField();
        addwidget->changeButtonName("Change");
        addwidget->setField(store[changeIndex]);
        addwidget->show();
    }
}
