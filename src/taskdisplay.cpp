#include <QDebug>
#include "taskdisplay.h"
#include "ui_taskdisplay.h"

TaskDisplay::TaskDisplay(int _index, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskDisplay),
    index(_index)
{
    ui->setupUi(this);
}

TaskDisplay::~TaskDisplay()
{
    delete ui;
}
