#ifndef TASKBAR_H
#define TASKBAR_H

#include <QWidget>
#include <QDialog>
#include "task.h"
#include "sidebar.h"

class TaskDisplay;

namespace Ui {
class TaskBar;
}

class TaskBar : public SideBar
{
    Q_OBJECT

public:
    explicit TaskBar(QWidget *anchor, int _taskIndex, QDate _today, QWidget *parent);
    ~TaskBar();

private slots:
    void on_pushButton_clicked(bool checked);
    void on_okButton_clicked(bool checked);
    void on_deleteButton_clicked(bool checked);
    void on_deleteAllButton_clicked(bool checked);
    void on_comboBox_activated(int index);
    void on_spinBox_valueChanged(int arg1);

private:
    Ui::TaskBar *ui;

    int taskIndex;

    TaskDisplay *taskDisplay;

    /// to be set after clicking save
    Task::RepeatType typeToSet;
    int intervalToSet;

    QDate today;
};

#endif // TASKBAR_H
