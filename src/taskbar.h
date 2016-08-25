#ifndef TASKBAR_H
#define TASKBAR_H

#include <QWidget>
#include <QDialog>
#include "sidebar.h"

class TaskDisplay;

namespace Ui {
class TaskBar;
}

class TaskBar : public SideBar
{
    Q_OBJECT

public:
    explicit TaskBar(QWidget *anchor, int _taskIndex, QWidget *parent = 0);
    ~TaskBar();

private slots:
    void deleteCancle(QDialog *dialog);
    void deleteSingle(QDialog *dialog);
    void deleteWhole(QDialog *dialog);

    void on_pushButton_clicked(bool checked);
    void on_okButton_clicked(bool checked);
    void on_deleteButton_clicked(bool checked);

private:
    Ui::TaskBar *ui;

    int taskIndex;

    TaskDisplay *taskDisplay;
};

#endif // TASKBAR_H
