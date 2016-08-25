#include <QFile>
#include <QList>
#include <QLabel>
#include <QDebug>
#include <QPalette>
#include <QComboBox>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QLayoutItem>
#include <QSignalMapper>
#include "data.h"
#include "tile.h"
#include "html.h"
#include "ui_tile.h"
#include "taskbar.h"
#include "tilebar.h"
#include "mainwindow.h"
#include "taskdisplay.h"
#include "ui_mainwindow.h"

MainWindow *MainWindow::myInstance = 0;

void MainWindow::createInstance()
{
    Q_ASSERT(myInstance == 0);
    myInstance = new MainWindow();
}

MainWindow *MainWindow::getMyInstance()
{
    Q_ASSERT(myInstance != 0);
    return myInstance;
}

void MainWindow::destroyInstance()
{
    delete myInstance;
    myInstance = 0;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    calendarData(new Data(this)),
    ui(new Ui::MainWindow),
    changingDate(false)
{
    ui->setupUi(this);

    if (! chinese.load(":/translation/zh_cn.qm"))
        qDebug() << "failed to load zh_cn.qm";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::postConstructInit()
{
    alterDisplayedDate(QDate::currentDate());
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
    changingDate = true;
    ui->yearBox->setValue(date.year());
    ui->monthBox->setValue(date.month());
    ui->dayBox->setValue(date.day());
    displayedDate = date;
    init();
    changingDate = false;
}

void MainWindow::clearGrid()
{
    QLayoutItem *child = 0;
    while ((child = ui->grid->takeAt(0)))
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
    {
        Tile *hHeader = new Tile(
            QColor(0x42, 0x37, 0x32, 0xD0),
            Html::white(Html::italic(headerText[i])),
            {}, false, ui->gridWidget
        );
        ui->grid->addWidget(hHeader, 0, i);
    }

    QDate iter(year, month, 1);
    while (iter.dayOfWeek() != 1) iter = iter.addDays(-1);
    int stWeek = iter.weekNumber();
    for (; iter < QDate(year, month, 1).addMonths(1) || iter.dayOfWeek() != 1; iter = iter.addDays(1))
    {
        if (iter.weekNumber() < stWeek) stWeek = 0;
        int rowId = iter.weekNumber() - stWeek + 1;
        QWidget *tile = dayInMonth(iter, iter.month() == month);
        ui->grid->addWidget(tile, rowId, iter.dayOfWeek());
        if (iter.dayOfWeek() == 1)
        {
            Tile *vHeader = new Tile(
                QColor(0x42, 0x37, 0x32, 0xD0),
                Html::white(Html::italic(QString::number(iter.weekNumber()))),
                {}, false, ui->gridWidget
            );
            ui->grid->addWidget(vHeader, rowId, 0);
        }
    }

    ui->grid->setRowStretch(0, 10);
    for (int i = 1; i < ui->grid->rowCount(); i++)
        ui->grid->setRowStretch(i, 20);
    ui->grid->setColumnStretch(0, 10);
    for (int i = 1; i < ui->grid->columnCount(); i++)
        ui->grid->setColumnStretch(i, 20);
}

QWidget *MainWindow::dayInMonth(QDate date, bool monthDisplayed)
{
    QString title = QString::number(date.day());
    if (! monthDisplayed) title = Html::gray(title);
    title = Html::strong(title);

    QColor color;
    if (date == QDate::currentDate())
        color = QColor(0x00, 0x3D, 0x99, 0xD0);
    else
        color = calendarData->getDayColor(date);

    QList<QWidget*> w;
    QList<int> tasks = calendarData->findTask(date);
    for (int i = 0; i < tasks.count(); i++)
    {
        TaskDisplay *task = new TaskDisplay(tasks[i], true, date, 0);
        w.push_back(task);
        connect(task, SIGNAL(onSelected(QWidget*,int,QDate)), this, SLOT(promptTaskBar(QWidget*,int,QDate)));
    }

    Tile *ret = new Tile(color, title, w, true, ui->gridWidget);

    ret->ui->title->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    QSignalMapper *mapper = new QSignalMapper(ret);
    connect(ret, SIGNAL(onSelected()), mapper, SLOT(map()));
    mapper->setMapping(ret, ret);
    connect(mapper, SIGNAL(mapped(QWidget*)), this, SLOT(promptTileBar(QWidget*)));

    widgetToDate[ret] = date;
    return ret;
}

void MainWindow::promptTaskBar(QWidget *task, int taskIndex, QDate today)
{
    qDebug() << "prompt task bar";
    new TaskBar(task, taskIndex, today, 0);
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
    if (changingDate) return;
    alterDisplayedDate(QDate(ui->yearBox->value(), ui->monthBox->value(), ui->dayBox->value()));
}

void MainWindow::on_monthBox_valueChanged(int)
{
    if (changingDate) return;
    alterDisplayedDate(QDate(ui->yearBox->value(), ui->monthBox->value(), ui->dayBox->value()));
}

void MainWindow::on_dayBox_valueChanged(int)
{
    if (changingDate) return;
    alterDisplayedDate(QDate(ui->yearBox->value(), ui->monthBox->value(), ui->dayBox->value()));
}

void MainWindow::on_exportButton_clicked(bool)
{
    QString destFile = QFileDialog::getSaveFileName(this, tr("Choose a filename"),
                                                    "calendarConf.json", "JSON files (*.json)");
    delete calendarData;
    calendarData = 0;
    if (QFile::exists(destFile))
    {
        qDebug() << "removing " << destFile;
        QFile::remove(destFile);
    }
    QFile::copy(Data::saveFile, destFile);
    calendarData = new Data(this);
}

void MainWindow::on_importButton_clicked(bool)
{
    QString destFile = QFileDialog::getOpenFileName(this, tr("Choose a file"));
    delete calendarData;
    calendarData = 0;
    if (QFile::exists(Data::saveFile))
    {
        qDebug() << "removing " << Data::saveFile;
        QFile::remove(Data::saveFile);
    }
    QFile::copy(destFile, Data::saveFile);
    calendarData = new Data(this);
    init();
}
