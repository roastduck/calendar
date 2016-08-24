#ifndef TILE_H
#define TILE_H

#include <QEvent>
#include <QWidget>
#include <QMouseEvent>

/// A QWidget with mouse event response
class Tile : public QWidget
{
    Q_OBJECT
public:
    explicit Tile(QWidget *parent = 0);

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    /// Emitted when the tile is selected by double clicking
    void onSelected();

};

#endif // TILE_H
