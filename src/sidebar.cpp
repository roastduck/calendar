#include <QDebug>
#include <QGraphicsBlurEffect>
#include "sidebar.h"

SideBar::SideBar(QWidget *_anchor, QWidget *parent)
    : QWidget(parent), anchor(_anchor)
{
    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect(anchor->window());
    anchor->window()->setGraphicsEffect(blur);
}

SideBar::~SideBar()
{
    qDebug() << "sidebar deleted";
    anchor->window()->setGraphicsEffect(0);
}

void SideBar::init()
{
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    // Qt::Popup used to close it when clicking outside
    setAttribute(Qt::WA_TranslucentBackground);
    move(anchor->mapToGlobal(anchor->mapFromParent(anchor->geometry().topRight())));
    show();
}

void SideBar::hideEvent(QHideEvent *event)
{
    deleteLater();
}
