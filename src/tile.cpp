#include <QDebug>
#include <QGraphicsColorizeEffect>
#include "tile.h"

Tile::Tile(QWidget *parent) : QWidget(parent) {}

void Tile::enterEvent(QEvent *event)
{
    qDebug() << "mouse entered";
    QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect();
    setGraphicsEffect(effect);
    QWidget::enterEvent(event);
}

void Tile::leaveEvent(QEvent *event)
{
    qDebug() << "mouse leaved";
    setGraphicsEffect(0);
    QWidget::leaveEvent(event);
}
