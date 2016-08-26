#ifndef LABELWITHCLICK_H
#define LABELWITHCLICK_H

#include <QLabel>
#include <QString>
#include <QMouseEvent>

class LabelWithClick : public QLabel
{
    Q_OBJECT
public:
    explicit LabelWithClick(const QString &text, QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void clicked();
};

#endif // LABELWITHCLICK_H
