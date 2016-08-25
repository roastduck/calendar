#include <QColor>
#include <QString>
#include "data.h"
#include "tilebar.h"
#include "mainwindow.h"
#include "ui_tilebar.h"

TileBar::TileBar(QWidget *anchor, QDate _date, QWidget *parent) :
    SideBar(anchor, parent),
    ui(new Ui::TileBar),
    date(_date)
{
    ui->setupUi(this);
    init();
    initColorBox();
}

TileBar::~TileBar()
{
    delete ui;
}

void TileBar::initColorBox()
{
    QColor currentColor = dynamic_cast<MainWindow*>(anchor->window())->calendarData->getDayColor(date);

    for (int i = 0; i < 4; i++)
    {
        QPixmap pix( QSize( 70, 20 ) );
        pix.fill(colors[i]);
        ui->colorBox->addItem(QIcon(pix), 0);
        ui->colorBox->setIconSize(QSize(70, 20));
        ui->colorBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        if (currentColor == colors[i])
            ui->colorBox->setCurrentIndex(i);
    }
}

void TileBar::on_colorBox_activated(int index)
{
    dynamic_cast<MainWindow*>(anchor->window())->calendarData->setDayColor(date, colors[index]);
    hide();
}

void TileBar::on_pushButton_clicked(bool)
{
    dynamic_cast<MainWindow*>(anchor->window())->calendarData->addTask(date);
    hide();
}
