#ifndef TILEBAR_H
#define TILEBAR_H

#include <QWidget>
#include "sidebar.h"

namespace Ui {
class TileBar;
}

class TileBar : public SideBar
{
    Q_OBJECT

public:
    explicit TileBar(QWidget *anchor, QWidget *parent = 0);
    ~TileBar();

private:
    Ui::TileBar *ui;
};

#endif // TILEBAR_H
