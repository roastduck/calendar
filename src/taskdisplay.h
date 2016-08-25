#ifndef TASKDISPLAY_H
#define TASKDISPLAY_H

#include <QWidget>

namespace Ui {
class TaskDisplay;
}

class TaskDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit TaskDisplay(int _index, QWidget *parent);
    ~TaskDisplay();

private:
    Ui::TaskDisplay *ui;

    int index;
};

#endif // TASKDISPLAY_H
