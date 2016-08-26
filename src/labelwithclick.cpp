#include "labelwithclick.h"

LabelWithClick::LabelWithClick(const QString &text, QWidget *parent): QLabel(text, parent) {}

void LabelWithClick::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
    QLabel::mousePressEvent(event);
}
