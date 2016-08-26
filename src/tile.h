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
    ~Tile();

    Ui::Tile *ui;

    void highlight();
    void removeHighlight();

protected:
    /// Eat all event when window is pinned
    bool event(QEvent *event);

    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    /// Emitted when the tile is selected by double clicking
    void onSelected();

private:
    bool hoverEffect;
};

#endif // TILE_H
