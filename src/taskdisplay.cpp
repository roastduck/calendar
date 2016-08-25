#include <QDebug>
#include <QGraphicsColorizeEffect>
#include "tile.h"
#include "data.h"
#include "task.h"
#include "mainwindow.h"
#include "taskdisplay.h"
#include "ui_taskdisplay.h"

TaskDisplay::TaskDisplay(int _index, bool _hoverEffect, QDate _today, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskDisplay),
    index(_index),
    hoverEffect(_hoverEffect),
    today(_today)
{
    ui->setupUi(this);
    ui->textEdit->setPlainText(MainWindow::getMyInstance()->calendarData->taskAt(index)->getContent());
}

TaskDisplay::~TaskDisplay()
{
    delete ui;
}

void TaskDisplay::enableEditor()
{
    ui->textEdit->setDisabled(false);
    ui->textEdit->setFocus();
}

QString TaskDisplay::getContent() const
{
    return ui->textEdit->toPlainText();
}

void TaskDisplay::enterEvent(QEvent *event)
{
    if (hoverEffect)
    {
        dynamic_cast<Tile*>(parent())->removeHighlight();
        QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect(this);
        setGraphicsEffect(effect);
    }
    QWidget::enterEvent(event);
}

void TaskDisplay::leaveEvent(QEvent *event)
{
    if (hoverEffect)
    {
        dynamic_cast<Tile*>(parent())->highlight();
        setGraphicsEffect(0);
    }
    QWidget::leaveEvent(event);
}

void TaskDisplay::mousePressEvent(QMouseEvent *event)
{
    if (hoverEffect && event->button() == Qt::RightButton)
    {
        emit onSelected(this, index, today);
        // no calling parent
    } else
        QWidget::mousePressEvent(event);
}

void TaskDisplay::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (hoverEffect)
    {
        emit onSelected(this, index, today);
        //no calling parent
    } else
        QWidget::mouseDoubleClickEvent(event);
}
