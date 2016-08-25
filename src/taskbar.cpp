#include <algorithm>
#include <QSizePolicy>
#include "data.h"
#include "task.h"
#include "taskbar.h"
#include "ui_taskbar.h"
#include "mainwindow.h"
#include "taskdisplay.h"
#include "deletetaskconfirm.h"

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
}

TaskBar::~TaskBar()
{
    delete ui;
}

void TaskBar::deleteCancle(QDialog *dialog)
{
    delete dialog;
}

void TaskBar::deleteSingle(QDialog *dialog)
{
    QDate day = MainWindow::getMyInstance()->calendarData->taskAt(taskIndex)->getBaseDate();
    MainWindow::getMyInstance()->calendarData->taskAt(taskIndex)->addExclude(day);
    delete dialog;
    hide();
}

void TaskBar::deleteWhole(QDialog *dialog)
{
    MainWindow::getMyInstance()->calendarData->delTask(taskIndex);
    delete dialog;
    hide(); // MUST. index changed.
}

void TaskBar::on_pushButton_clicked(bool)
{
    hide();
}

void TaskBar::on_okButton_clicked(bool)
{
    MainWindow::getMyInstance()->calendarData->taskAt(taskIndex)->setContent(taskDisplay->getContent());
    hide();
}

void TaskBar::on_deleteButton_clicked(bool)
{
    bool isRepeatTask = (MainWindow::getMyInstance()->calendarData->taskAt(taskIndex)->getRepeatType() != Task::NONE);
    DeleteTaskConfirm *dialog = new DeleteTaskConfirm(isRepeatTask);
    connect(dialog, SIGNAL(cancel(QDialog*)), this, SLOT(deleteCancle(QDialog*)));
    connect(dialog, SIGNAL(single(QDialog*)), this, SLOT(deleteSingle(QDialog*)));
    connect(dialog, SIGNAL(whole(QDialog*)), this, SLOT(deleteWhole(QDialog*)));
    dialog->show();
}
