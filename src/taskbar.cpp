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
    MainWindow::getMyInstance()->calendarData->taskAt(taskIndex)->setContent(taskDisplay->getContent());
    hide();
}
