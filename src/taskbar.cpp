#include <QRect>
#include <QDebug>
#include <algorithm>
#include <QSizePolicy>
#include "data.h"
#include "task.h"
#include "taskbar.h"
#include "ui_taskbar.h"
#include "mainwindow.h"
#include "taskdisplay.h"

TaskBar::TaskBar(QWidget *anchor, int _taskIndex, QDate _today, QWidget *parent) :
    SideBar(anchor, false, parent),
    ui(new Ui::TaskBar),
    taskIndex(_taskIndex),
    today(_today)
{
    ui->setupUi(this);

    init();
    move(anchor->mapToGlobal(anchor->mapFromParent(anchor->geometry().topLeft())));

    taskDisplay = new TaskDisplay(taskIndex, false, today, ui->editor);
    ui->editor->layout()->addWidget(taskDisplay);
    taskDisplay->enableEditor();

    typeToSet = MainWindow::getMyInstance()->calendarData->taskAt(taskIndex)->getRepeatType();

    ui->comboBox->setCurrentIndex((int)typeToSet);
    if (typeToSet == Task::NONE)
    {
        ui->deleteButton->hide();
        ui->spinBox->setDisabled(true);
    }
    ui->spinBox->setValue(intervalToSet = MainWindow::getMyInstance()->calendarData->taskAt(taskIndex)->getRepeatInterval());

    int childRight = anchor->mapToGlobal(anchor->mapFromParent(anchor->geometry().topRight())).x();
    int myRight = ui->editor->mapToGlobal(ui->editor->mapFromParent(ui->editor->geometry().topRight())).x();
    qDebug() << childRight << " -- " << myRight;
    if (childRight > myRight)
        resize(width() + childRight - myRight, height());

    int childDown = anchor->mapToGlobal(anchor->mapFromParent(anchor->geometry().bottomLeft())).y();
    int myDown = ui->editor->mapToGlobal(ui->editor->mapFromParent(ui->editor->geometry().bottomLeft())).y();
    qDebug() << childDown << " -- " << myDown;
    if (childDown > myDown)
        resize(width(), height() + childDown - myDown);
}

TaskBar::~TaskBar()
{
    delete ui;
}

void TaskBar::on_pushButton_clicked(bool)
{
    hide();
}

void TaskBar::on_okButton_clicked(bool)
{
    Task *task = MainWindow::getMyInstance()->calendarData->taskAt(taskIndex);
    task->setContent(taskDisplay->getContent());
    task->setRepeatType(typeToSet);
    task->setRepeatInterval(intervalToSet);
    hide();
}

void TaskBar::on_deleteButton_clicked(bool)
{
    MainWindow::getMyInstance()->calendarData->taskAt(taskIndex)->addExclude(today);
    hide();
}

void TaskBar::on_deleteAllButton_clicked(bool)
{
    MainWindow::getMyInstance()->calendarData->delTask(taskIndex);
    hide(); // MUST. index changed.
}

void TaskBar::on_comboBox_activated(int index)
{
    qDebug() << "type choosed " << index;
    typeToSet = (Task::RepeatType)index;
    ui->spinBox->setDisabled(typeToSet == Task::NONE);
}

void TaskBar::on_spinBox_valueChanged(int arg1)
{
    intervalToSet = arg1;
}
