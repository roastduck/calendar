#include <QDebug>
#include <algorithm>
#include <QSizePolicy>
#include "data.h"
#include "task.h"
#include "taskbar.h"
#include "ui_taskbar.h"
#include "mainwindow.h"
#include "taskdisplay.h"

TaskBar::TaskBar(QWidget *anchor, int _taskIndex, QWidget *parent) :
    SideBar(anchor, false, parent),
    ui(new Ui::TaskBar),
    taskIndex(_taskIndex)
{
    ui->setupUi(this);

    init();
    move(anchor->mapToGlobal(anchor->mapFromParent(anchor->geometry().topLeft())));

    taskDisplay = new TaskDisplay(taskIndex, false, ui->editor);
    ui->editor->layout()->addWidget(taskDisplay);
    taskDisplay->enableEditor();

    Task::RepeatType t = MainWindow::getMyInstance()->calendarData->taskAt(taskIndex)->getRepeatType();

    ui->comboBox->setCurrentIndex((int)t);
    if (t == Task::NONE)
    {
        ui->deleteButton->hide();
        ui->spinBox->setDisabled(true);
    } else
        ui->spinBox->setValue(MainWindow::getMyInstance()->calendarData->taskAt(taskIndex)->getRepeatInterval());
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
    QDate day = MainWindow::getMyInstance()->calendarData->taskAt(taskIndex)->getBaseDate();
    MainWindow::getMyInstance()->calendarData->taskAt(taskIndex)->addExclude(day);
    hide();
}

void TaskBar::on_deleteAllButton_clicked(bool)
{
    MainWindow::getMyInstance()->calendarData->delTask(taskIndex);
    hide(); // MUST. index changed.
}

void TaskBar::on_comboBox_activated(int index)
{
    qDebug() << "choose " << index;
    typeToSet = (Task::RepeatType)index;
    ui->spinBox->setDisabled(typeToSet == Task::NONE);
}

void TaskBar::on_spinBox_valueChanged(int arg1)
{
    intervalToSet = arg1;
}
