#ifndef TILE_H
#define TILE_H

#include <QList>
#include <QColor>
#include <QEvent>
#include <QString>
#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class Tile;
}

/// A grid cell response for a day
class Tile : public QWidget
{
    Q_OBJECT
public:
    /**
     * @param color : background color
     * @param _hoverEffect : whether to change color when hover
     */
    explicit Tile(QColor color, QString title, QList<QWidget*> body, bool _hoverEffect, QWidget *parent);

    Ui::Tile *ui;

    void highlight();
    void removeHighlight();

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    /// Emitted when the tile is selected by double clicking
    void onSelected();

private:
    bool hoverEffect;
};

#endif // TILE_H
