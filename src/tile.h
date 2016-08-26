#ifndef TILE_H
#define TILE_H

#include <QList>
#include <QDate>
#include <QColor>
#include <QEvent>
#include <QString>
#include <QWidget>
#include <QDropEvent>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>

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
     * @param isDay : this tile repersents a day rather than a title
     */
    explicit Tile(QColor color, QString title, QList<QWidget*> body,
                  bool isDay, QWidget *parent, const QDate &_today = QDate());
    ~Tile();

    Ui::Tile *ui;

    void highlight();
    void removeHighlight();

protected:
    /// Eat all event when window is pinned
    bool event(QEvent *event);

    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    /// Emitted when the tile is selected by double clicking
    void onSelected();
    void requireRefresh();

private:
    bool hoverEffect;
    QDate today;
};

#endif // TILE_H
