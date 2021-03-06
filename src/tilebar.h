#ifndef TILEBAR_H
#define TILEBAR_H

#include <QDate>
#include <QWidget>
#include "sidebar.h"

namespace Ui {
class TileBar;
}

/// The side bar besides a day in the calendar
class TileBar : public SideBar
{
    Q_OBJECT

public:
    explicit TileBar(QWidget *anchor, QDate _date, QWidget *parent = 0);
    ~TileBar();

private slots:
    void on_colorBox_activated(int index);
    void on_pushButton_clicked(bool checked);

private:
    void initColorBox();

    const QColor colors[4] = {
        QColor(0xE0, 0xFF, 0x85, 0xD0),
        QColor(0xFF, 0x00, 0x00, 0xD0),
        QColor(0x00, 0xFF, 0x00, 0xD0),
        QColor(0x00, 0x00, 0xFF, 0xD0)
    };

    Ui::TileBar *ui;

    QDate date;
};

#endif // TILEBAR_H
