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
    for (int i = 0; i < 4; i++)
    {
        QPixmap pix( QSize( 70, 20 ) );
        pix.fill(colors[i]);
        ui->colorBox->addItem(QIcon(pix), 0);
        ui->colorBox->setIconSize(QSize(70, 20));
        ui->colorBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    }
}

void TileBar::on_colorBox_currentIndexChanged(int index)
{
    dynamic_cast<MainWindow*>(anchor->window())->calendarData->setDayColor(date, colors[index]);
}
