#include <QDebug>
#include <QGraphicsBlurEffect>
#include "sidebar.h"
#include "mainwindow.h"

SideBar::SideBar(QWidget *_anchor, bool _clickToLeave, QWidget *parent)
    : QWidget(parent), anchor(_anchor), clickToLeave(_clickToLeave)
{
    qDebug() << "blur set";
    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect(MainWindow::getMyInstance());
    MainWindow::getMyInstance()->setGraphicsEffect(blur); // right click on tile twice will make effect. why?
}

SideBar::~SideBar()
{
    qDebug() << "blur unset";
    MainWindow::getMyInstance()->setGraphicsEffect(0);
    MainWindow::getMyInstance()->init(); // NOTICE: this will destory anchor
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
