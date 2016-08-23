#include <QLabel>
#include <QPalette>
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

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint windowPos = pos();
    QPoint mousePos = event->globalPos();
    dPos = mousePos - windowPos;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPos() - dPos);
}

void MainWindow::clearGrid()
{
    for (QLayoutItem *child = ui->grid->takeAt(0); child;)
        delete child;
}

void MainWindow::initMonth(int year, int month)
{
    clearGrid();

    const char *headerText[] = { "Week", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
    for (int i = 0; i <= 7; i++)
        ui->grid->addWidget(newCell(
            new QLabel(Html::white(Html::italic(tr(headerText[i])))),
            QColor(0x42, 0x37, 0x32, 0xD0)
        ), 0, i);

    QDate iter(year, month, 1);
    while (iter.dayOfWeek() != 1) iter = iter.addDays(-1);
    int stWeek = iter.weekNumber();
    for (; iter.month() == month || iter.dayOfWeek() != 1; iter = iter.addDays(1))
    {
        int rowId = iter.weekNumber() - stWeek + 1;
        ui->grid->addWidget(dayInMonth(iter, iter.month() == month), rowId, iter.dayOfWeek());
        if (iter.dayOfWeek() == 1)
            ui->grid->addWidget(newCell(
                new QLabel(Html::white(Html::italic(QString::number(iter.weekNumber())))),
                QColor(0x42, 0x37, 0x32, 0xD0)
            ), rowId, 0);
    }
}

QWidget *MainWindow::newCell(QWidget *w, QColor c)
{
    QWidget *ret = new QWidget();
    QPalette palette = ret->palette();
    palette.setColor(QPalette::Window, c);
    ret->setPalette(palette);
    ret->setAutoFillBackground(true);
    w->setParent(ret);
    return ret;
}

QWidget *MainWindow::dayInMonth(QDate date, bool monthDisplayed)
{
    QString title = QString::number(date.day());
    if (! monthDisplayed) title = Html::gray(title);
    QLabel *label = new QLabel(Html::strong(title));

    QColor color(0xE0, 0xFF, 0x85, 0xD0);
    if (date == QDate::currentDate())
        color = QColor(0x00, 0x3D, 0x99, 0xD0);
    return newCell(label, color);
}

void MainWindow::on_quitButton_released()
{
    qApp->exit();
}
