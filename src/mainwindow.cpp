#include <QLabel>
#include <QDebug>
#include <QPalette>
#include <QComboBox>
#include <QVBoxLayout>
#include <QLayoutItem>
#include <QSignalMapper>
#include "data.h"
#include "tile.h"
#include "html.h"
#include "tilebar.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    calendarData(new Data(this)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (! chinese.load(":/translation/zh_cn.qm"))
        qDebug() << "failed to load zh_cn.qm";

    alterDisplayedDate(QDate::currentDate());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    initMonth();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint windowPos = pos();
    QPoint mousePos = event->globalPos();
    dPos = mousePos - windowPos;
    QMainWindow::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPos() - dPos);
    QMainWindow::mouseMoveEvent(event);
}

void MainWindow::alterDisplayedDate(QDate date)
{
    ui->yearBox->setValue(date.year());
    ui->monthBox->setValue(date.month());
    ui->dayBox->setValue(date.day());
    displayedDate = date;
    init();
}

void MainWindow::clearGrid()
{
    QLayoutItem *child = 0;
    while (child = ui->grid->takeAt(0))
        delete child->widget();
    widgetToDate.clear();
}

void MainWindow::initMonth()
{
    clearGrid();

    ui->yearBox->show();
    ui->monthBox->show();
    ui->dayBox->hide();
    ui->yearMonthLabel->show();
    ui->monthDayLabel->hide();

    int year = displayedDate.year();
    int month = displayedDate.month();

    QString headerText[] = { tr("Week"), tr("Mon"), tr("Tue"), tr("Wed"), tr("Thu"), tr("Fri"), tr("Sat"), tr("Sun") };
    for (int i = 0; i <= 7; i++)
        ui->grid->addWidget(newCell(
            new QLabel(Html::white(Html::italic(headerText[i]))),
            QColor(0x42, 0x37, 0x32, 0xD0)
        ), 0, i);

    QDate iter(year, month, 1);
    while (iter.dayOfWeek() != 1) iter = iter.addDays(-1);
    int stWeek = iter.weekNumber();
    for (; iter < QDate(year, month, 1).addMonths(1) || iter.dayOfWeek() != 1; iter = iter.addDays(1))
    {
        if (iter.weekNumber() < stWeek) stWeek = 0;
        int rowId = iter.weekNumber() - stWeek + 1;
        ui->grid->addWidget(dayInMonth(iter, iter.month() == month), rowId, iter.dayOfWeek());
        if (iter.dayOfWeek() == 1)
            ui->grid->addWidget(newCell(
                new QLabel(Html::white(Html::italic(QString::number(iter.weekNumber())))),
                QColor(0x42, 0x37, 0x32, 0xD0)
            ), rowId, 0);
    }

    ui->grid->setRowStretch(0, 10);
    for (int i = 1; i < ui->grid->rowCount(); i++)
        ui->grid->setRowStretch(i, 20);
    ui->grid->setColumnStretch(0, 10);
    for (int i = 1; i < ui->grid->columnCount(); i++)
        ui->grid->setColumnStretch(i, 20);
}

QWidget *MainWindow::newCell(QWidget *w, QColor c, bool mouseBehavior)
{
    QWidget *ret = 0;
    if (mouseBehavior)
    {
        ret = new Tile();
        QSignalMapper *mapper = new QSignalMapper(ret);
        connect(ret, SIGNAL(onSelected()), mapper, SLOT(map()));
        mapper->setMapping(ret, ret);
        connect(mapper, SIGNAL(mapped(QWidget*)), this, SLOT(promptTileBar(QWidget*)));
    } else
        ret = new QWidget();
    QPalette palette = ret->palette();
    palette.setColor(QPalette::Window, c);
    ret->setPalette(palette);
    ret->setAutoFillBackground(true);

    QVBoxLayout *layout = new QVBoxLayout(ret);

    w->setAttribute(Qt::WA_TransparentForMouseEvents);
    layout->addWidget(w);

    return ret;
}

QWidget *MainWindow::dayInMonth(QDate date, bool monthDisplayed)
{
    QString title = QString::number(date.day());
    if (! monthDisplayed) title = Html::gray(title);
    QLabel *label = new QLabel(Html::strong(title));
    label->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    QColor color;
    if (date == QDate::currentDate())
        color = QColor(0x00, 0x3D, 0x99, 0xD0);
    else
        color = calendarData->getDayColor(date);
    QWidget *ret = newCell(label, color, true);
    widgetToDate[ret] = date;
    return ret;
}

void MainWindow::promptTileBar(QWidget *tile)
{    
    qDebug() << "prmopt tile bar";
    new TileBar(tile, widgetToDate[tile]);
}

void MainWindow::on_comboBox_activated(int index)
{
    qDebug() << "language switched to " << index;
    if (index == 1) // chinese
        qApp->installTranslator(&chinese);
    else
        qApp->removeTranslator(&chinese);
    ui->retranslateUi(this);
    init();
    ui->comboBox->setCurrentIndex(index);
}

void MainWindow::on_quitButton_clicked(bool)
{
    qApp->exit();
}

void MainWindow::on_previousButton_clicked(bool)
{
    alterDisplayedDate(displayedDate.addMonths(-1));
}

void MainWindow::on_nextButton_clicked(bool)
{
    alterDisplayedDate(displayedDate.addMonths(1));
}

void MainWindow::on_yearBox_valueChanged(int)
{
    alterDisplayedDate(QDate(ui->yearBox->value(), ui->monthBox->value(), ui->dayBox->value()));
}

void MainWindow::on_monthBox_valueChanged(int)
{
    alterDisplayedDate(QDate(ui->yearBox->value(), ui->monthBox->value(), ui->dayBox->value()));
}

void MainWindow::on_dayBox_valueChanged(int)
{
    alterDisplayedDate(QDate(ui->yearBox->value(), ui->monthBox->value(), ui->dayBox->value()));
}
