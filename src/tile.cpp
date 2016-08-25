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
    ui->title->setAttribute(Qt::WA_TransparentForMouseEvents);

    for (int i = 0; i < body.count(); i++)
    {
        //body[i]->setAttribute(Qt::WA_TransparentForMouseEvents);
        layout()->addWidget(body[i]);
    }
}

Tile::~Tile()
{
    delete ui;
}

void Tile::highlight()
{
    QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect(this);
    setGraphicsEffect(effect);
}

void Tile::removeHighlight()
{
    setGraphicsEffect(0);
}

void Tile::enterEvent(QEvent *event)
{
    if (hoverEffect) highlight();
    QWidget::enterEvent(event);
}

void Tile::leaveEvent(QEvent *event)
{
    if (hoverEffect) removeHighlight();
    QWidget::leaveEvent(event);
}

void Tile::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
        emit onSelected();
    QWidget::mousePressEvent(event);
}

void Tile::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit onSelected();
    QWidget::mouseDoubleClickEvent(event);
}
