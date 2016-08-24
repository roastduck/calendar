#include "tilebar.h"
#include "ui_tilebar.h"

TileBar::TileBar(QWidget *anchor, QWidget *parent) :
    SideBar(parent),
    ui(new Ui::TileBar)
{
    ui->setupUi(this);
    init(anchor);
}

TileBar::~TileBar()
{
    delete ui;
}
