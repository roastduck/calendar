#include <QDebug>
#include <QGraphicsColorizeEffect>
#include "tile.h"

Tile::Tile(QWidget *parent) : QWidget(parent) {}

void Tile::enterEvent(QEvent *event)
{
    QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect();
    setGraphicsEffect(effect);
    QWidget::enterEvent(event);
}

void Tile::leaveEvent(QEvent *event)
{
    setGraphicsEffect(0);
    QWidget::leaveEvent(event);
}

void Tile::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit onSelected();
}
