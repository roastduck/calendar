#include "tilebar.h"
#include "ui_tilebar.h"

TileBar::TileBar(QWidget *anchor, QWidget *parent) :
    SideBar(anchor, parent),
    ui(new Ui::TileBar)
{
    ui->setupUi(this);
    init();
}

TileBar::~TileBar()
{
    delete ui;
}
