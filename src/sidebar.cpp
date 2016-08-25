#include <QDebug>
#include <QGraphicsBlurEffect>
#include "sidebar.h"
#include "mainwindow.h"

SideBar::SideBar(QWidget *_anchor, bool _clickToLeave, QWidget *parent)
    : QWidget(parent), anchor(_anchor), clickToLeave(_clickToLeave)
{
    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect(anchor->window());
    anchor->window()->setGraphicsEffect(blur);
}

SideBar::~SideBar()
{
    qDebug() << "sidebar deleted";
    anchor->window()->setGraphicsEffect(0);
    dynamic_cast<MainWindow*>(anchor->window())->init(); // NOTICE: this will destory anchor
}

void SideBar::init()
{
    setWindowModality(Qt::ApplicationModal);
    if (clickToLeave)
        setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    else
        setWindowFlags(Qt::FramelessWindowHint);
    // Qt::Popup used to close it when clicking outside
    setAttribute(Qt::WA_TranslucentBackground);
    show();
}

void SideBar::hideEvent(QHideEvent *)
{
    deleteLater();
}
