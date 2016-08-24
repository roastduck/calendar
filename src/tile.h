#ifndef TILE_H
#define TILE_H

#include <QEvent>
#include <QWidget>

/// A QWidget with mouse event response
class Tile : public QWidget
{
    Q_OBJECT
public:
    explicit Tile(QWidget *parent = 0);

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

signals:

};

#endif // TILE_H
