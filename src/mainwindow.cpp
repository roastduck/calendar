#include <QFile>
#include <QList>
#include <QIcon>
#include <QRect>
#include <QLabel>
#include <QDebug>
#include <QPoint>
#include <QRegion>
#include <QPalette>
#include <QComboBox>
#include <QGridLayout>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QLayoutItem>
#include <QSignalMapper>
#include "data.h"
#include "file.h"
#include "tile.h"
#include "html.h"
#include "ui_tile.h"
#include "taskbar.h"
#include "tilebar.h"
#include "mainwindow.h"
#include "taskdisplay.h"
#include "filedisplay.h"
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
    displayMode(MONTH),
    isDragging(false),
    changingDate(false),
    pinned(false)
{
    ui->setupUi(this);

    if (! chinese.load(":/translation/zh_cn.qm"))
        qDebug() << "failed to load zh_cn.qm";

    if (calendarData->isChinese())
    {
        qApp->installTranslator(&chinese);
        ui->retranslateUi(this);
        ui->comboBox->setCurrentIndex(1);
    }
    ui->dragSwitchButton->setChecked(calendarData->dragDisabled());
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
    qDebug() << "refreshed";
    switch (displayMode)
    {
    case MONTH:
        initMonth();
        break;
    case DAY:
        initDay();
        break;
    case WEEK:
        initWeek();
        break;
    default:
        qDebug() << "displayMode = " << displayMode;
        Q_ASSERT(false);
    }
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
    QGridLayout *grid = dynamic_cast<QGridLayout*>(ui->gridWidget->layout());
    for (int i = 0; i < grid->rowCount(); i++)
        grid->setRowStretch(i, 0);
    for (int i = 0; i < grid->columnCount(); i++)
        grid->setColumnStretch(i, 0);
    QLayoutItem *child = 0;
    while ((child = grid->takeAt(0)))
        child->widget()->deleteLater();
    widgetToDate.clear();
}

void MainWindow::showYMD()
{
    ui->yearBox->show();
    ui->monthBox->show();
    ui->dayBox->show();
    ui->yearMonthLabel->show();
    ui->monthDayLabel->show();
}

void MainWindow::showYM()
{
    ui->yearBox->show();
    ui->monthBox->show();
    ui->dayBox->hide();
    ui->yearMonthLabel->show();
    ui->monthDayLabel->hide();
}

void MainWindow::showY()
{
    ui->yearBox->show();
    ui->monthBox->hide();
    ui->dayBox->hide();
    ui->yearMonthLabel->hide();
    ui->monthDayLabel->hide();
}

void MainWindow::initMonth()
{
    clearGrid();
    showYM();

    QGridLayout *grid = dynamic_cast<QGridLayout*>(ui->gridWidget->layout());
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
        grid->addWidget(hHeader, 0, i);
    }

    QDate iter(year, month, 1);
    while (iter.dayOfWeek() != 1) iter = iter.addDays(-1);
    int stWeek = iter.weekNumber();
    for (; iter < QDate(year, month, 1).addMonths(1) || iter.dayOfWeek() != 1; iter = iter.addDays(1))
    {
        if (iter.weekNumber() < stWeek) stWeek = 0;
        int rowId = iter.weekNumber() - stWeek + 1;
        QWidget *tile = dayInMonth(iter, iter.month() == month);
        grid->addWidget(tile, rowId, iter.dayOfWeek());
        if (iter.dayOfWeek() == 1)
        {
            Tile *vHeader = new Tile(
                QColor(0x42, 0x37, 0x32, 0xD0),
                Html::white(Html::italic(QString::number(iter.weekNumber()))),
                {}, false, ui->gridWidget
            );
            grid->addWidget(vHeader, rowId, 0);
        }
    }

    grid->setRowStretch(0, 10);
    for (int i = 1; i < grid->rowCount(); i++)
        grid->setRowStretch(i, 20);
    grid->setColumnStretch(0, 10);
    for (int i = 1; i < grid->columnCount(); i++)
        grid->setColumnStretch(i, 20);
}

void MainWindow::initDay()
{
    clearGrid();
    showYMD();

    QGridLayout *grid = dynamic_cast<QGridLayout*>(ui->gridWidget->layout());
    QWidget *tile = dayInMonth(displayedDate, true);
    grid->addWidget(tile, 0, 0);
}

void MainWindow::initWeek()
{
    clearGrid();
    showYMD();

    QGridLayout *grid = dynamic_cast<QGridLayout*>(ui->gridWidget->layout());
    int month = displayedDate.month();

    QString headerText[] = { tr("Week"), tr("Mon"), tr("Tue"), tr("Wed"), tr("Thu"), tr("Fri"), tr("Sat"), tr("Sun") };
    for (int i = 0; i <= 7; i++)
    {
        Tile *hHeader = new Tile(
            QColor(0x42, 0x37, 0x32, 0xD0),
            Html::white(Html::italic(headerText[i])),
            {}, false, ui->gridWidget
        );
        grid->addWidget(hHeader, 0, i);
    }

    QDate iter(displayedDate);
    while (iter.dayOfWeek() != 1) iter = iter.addDays(-1);

    Tile *vHeader = new Tile(
        QColor(0x42, 0x37, 0x32, 0xD0),
        Html::white(Html::italic(QString::number(iter.weekNumber()))),
        {}, false, ui->gridWidget
    );
    grid->addWidget(vHeader, 1, 0);

    for (int i = 0; i < 7; i++, iter = iter.addDays(1))
        grid->addWidget(dayInMonth(iter, iter.month() == month), 1, iter.dayOfWeek());

    grid->setRowStretch(0, 10);
    grid->setRowStretch(1, 60);
    grid->setColumnStretch(0, 10);
    for (int i = 1; i < grid->columnCount(); i++)
        grid->setColumnStretch(i, 20);
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
    QList<File*> files = calendarData->getFile(date);
    for (int i = 0; i < files.count(); i++)
    {
        FileDisplay *file = new FileDisplay(date, i, 0);
        w.push_back(file);
        connect(file, SIGNAL(requireRefresh()), this, SLOT(init()));
    }

    Tile *ret = new Tile(color, title, w, true, ui->gridWidget, date);

    ret->ui->title->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    QSignalMapper *mapper = new QSignalMapper(ret);
    connect(ret, SIGNAL(onSelected()), mapper, SLOT(map()));
    mapper->setMapping(ret, ret);
    connect(mapper, SIGNAL(mapped(QWidget*)), this, SLOT(promptTileBar(QWidget*)));

    connect(ret, SIGNAL(requireRefresh()), this, SLOT(init()));

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
    {
        calendarData->setChinese(true);
        qApp->installTranslator(&chinese);
    } else
    {
        calendarData->setChinese(false);
        qApp->removeTranslator(&chinese);
    }
    ui->retranslateUi(this);
    init();
    ui->comboBox->setCurrentIndex(index);
}

void MainWindow::on_quitButton_clicked(bool)
{
    qApp->exit();
}

void MainWindow::addToDate(int x)
{
    switch (displayMode)
    {
    case MONTH:
        alterDisplayedDate(displayedDate.addMonths(x));
        break;
    case DAY:
    case TASK:
        alterDisplayedDate(displayedDate.addDays(x));
        break;
    case WEEK:
        alterDisplayedDate(displayedDate.addDays(x * 7));
        break;
    case YEAR:
        alterDisplayedDate(displayedDate.addYears(x));
        break;
    default:
        Q_ASSERT(false);
    }
}

void MainWindow::on_previousButton_clicked(bool)
{
    addToDate(-1);
}

void MainWindow::on_nextButton_clicked(bool)
{
    addToDate(1);
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

void MainWindow::on_pinButton_clicked(bool)
{
    if (! pinned)
    {
        pinned = true;

        ui->pinButton->setIcon(QIcon(":/icon/pinned.ico"));

        QPoint topLeft1 = ui->pinButton->mapTo(this, QPoint(0, 0));
        QRegion mask1(topLeft1.x(), topLeft1.y(), ui->pinButton->geometry().width(), ui->pinButton->geometry().height());

        QPoint topLeft2 = ui->gridWidget->mapTo(this, QPoint(0, 0));
        QRegion mask2(topLeft2.x(), topLeft2.y(), ui->gridWidget->geometry().width(), ui->gridWidget->geometry().height());

        setMask(mask1 + mask2);
    } else
    {
        pinned = false;

        ui->pinButton->setIcon(QIcon(":/icon/pin.ico"));

        clearMask();
    }
}

void MainWindow::on_dragSwitchButton_clicked(bool checked)
{
    calendarData->disableDrag(checked);
}

void MainWindow::on_dragSwitchButton_toggled(bool checked)
{
    if (checked)
        ui->dragSwitchButton->setIcon(QIcon(":/icon/file-transfer-cross.ico"));
    else
        ui->dragSwitchButton->setIcon(QIcon(":/icon/file-transfer-checkmark.ico"));
}

void MainWindow::on_modeBox_activated(int index)
{
    displayMode = (DisplayMode)index;
    init();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    isDragging = true;
    QPoint windowPos = pos();
    QPoint mousePos = event->globalPos();
    dPos = mousePos - windowPos;
    QMainWindow::mousePressEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    isDragging = false;
    QMainWindow::mouseReleaseEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (isDragging)
        move(event->globalPos() - dPos);
    QMainWindow::mouseMoveEvent(event);
}
