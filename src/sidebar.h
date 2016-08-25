#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>

/// Base class for side bar besides a day or a task
class SideBar : public QWidget
{
    Q_OBJECT
public:
    /**
     * @param _anchor : to show from which widget's
     * @param _clickToLeave : click anywhere outside to exit
     */
    explicit SideBar(QWidget *_anchor, bool _clickToLeave, QWidget *parent = 0);
    ~SideBar();

    void init();

protected:
    void hideEvent(QHideEvent *event);

    QWidget *anchor;

    bool clickToLeave;
};

#endif // SIDEBAR_H
