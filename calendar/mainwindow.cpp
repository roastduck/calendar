#include <QLabel>
#include <QLayoutItem>
#include "html.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initMonth(2016, 8);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearGrid()
{
    for (QLayoutItem *child = ui->grid->takeAt(0); child;)
        delete child;
}

void MainWindow::initMonth(int year, int month)
{
    clearGrid();

    ui->grid->addWidget(new QLabel(Html::italic(tr("Week"))), 0, 0);
    ui->grid->addWidget(new QLabel(Html::italic(tr("Mon"))), 0, 1);
    ui->grid->addWidget(new QLabel(Html::italic(tr("Tue"))), 0, 2);
    ui->grid->addWidget(new QLabel(Html::italic(tr("Wed"))), 0, 3);
    ui->grid->addWidget(new QLabel(Html::italic(tr("Thu"))), 0, 4);
    ui->grid->addWidget(new QLabel(Html::italic(tr("Fri"))), 0, 5);
    ui->grid->addWidget(new QLabel(Html::italic(tr("Sat"))), 0, 6);
    ui->grid->addWidget(new QLabel(Html::italic(tr("Sun"))), 0, 7);

    QDate iter(year, month, 1);
    while (iter.dayOfWeek() != 1) iter = iter.addDays(-1);
    int stWeek = iter.weekNumber();
    for (; iter.month() == month || iter.dayOfWeek() != 1; iter = iter.addDays(1))
    {
        int rowId = iter.weekNumber() - stWeek + 1;
        ui->grid->addWidget(dayInMonth(iter, iter.month() == month), rowId, iter.dayOfWeek());
        if (iter.dayOfWeek() == 1)
            ui->grid->addWidget(new QLabel(Html::italic(QString::number(iter.weekNumber()))), rowId, 0);
    }
}

QWidget *MainWindow::dayInMonth(QDate date, bool monthDisplayed)
{
    QString ret = QString::number(date.day());
    if (! monthDisplayed) ret = Html::gray(ret);
    return new QLabel(Html::strong(ret));
}
