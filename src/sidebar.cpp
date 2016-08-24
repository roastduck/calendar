#include "sidebar.h"

SideBar::SideBar(QWidget *parent) : QWidget(parent) {}

void SideBar::init(QWidget *anchor)
{
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    // Qt::Popup used to close it when clicking outside
    setAttribute(Qt::WA_TranslucentBackground);
    move(anchor->mapToGlobal(anchor->mapFromParent(anchor->geometry().topRight())));
    show();
}
