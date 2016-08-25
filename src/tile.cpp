#include <QDebug>
#include <QPalette>
#include <QGraphicsColorizeEffect>
#include "tile.h"
#include "ui_tile.h"

Tile::Tile(QColor color, QString title, QList<QWidget*> body, bool _hoverEffect, QWidget *parent)
    : QWidget(parent),
      ui(new Ui::Tile()),
      hoverEffect(_hoverEffect)
{
    ui->setupUi(this);

    QPalette thisPalette = palette();
    thisPalette.setColor(QPalette::Window, color);
    setPalette(thisPalette);

    ui->title->setText(title);

    for (int i = 0; i < body.count(); i++)
    {
        //if (body[i]->metaObject()->className() != QString("TaskDisplay"))
        body[i]->setAttribute(Qt::WA_TransparentForMouseEvents);
        layout()->addWidget(body[i]);
    }
}

void Tile::enterEvent(QEvent *event)
{
    if (! hoverEffect) return;
    QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect(this);
    setGraphicsEffect(effect);
    QWidget::enterEvent(event);
}

void Tile::leaveEvent(QEvent *event)
{
    if (! hoverEffect) return;
    setGraphicsEffect(0);
    QWidget::leaveEvent(event);
}

void Tile::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit onSelected();
    QWidget::mouseDoubleClickEvent(event);
}
