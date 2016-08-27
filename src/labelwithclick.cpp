#include "mainwindow.h"
#include "labelwithclick.h"

LabelWithClick::LabelWithClick(const QString &text, QWidget *parent): QLabel(text, parent) {}

void LabelWithClick::mousePressEvent(QMouseEvent *event)
{
    if (MainWindow::getMyInstance()->isPinned()) return;
    emit clicked();
    QLabel::mousePressEvent(event);
}
