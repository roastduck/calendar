#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>

class SideBar : public QWidget
{
    Q_OBJECT
public:
    explicit SideBar(QWidget *_anchor, QWidget *parent = 0);
    ~SideBar();

    void init();

protected:
    void hideEvent(QHideEvent *event);

private:
    QWidget *anchor;
};

#endif // SIDEBAR_H
