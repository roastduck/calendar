#ifndef HELP_H
#define HELP_H

#include <QList>
#include <QMovie>
#include <QString>
#include <QDialog>

namespace Ui {
class Help;
}

class Help : public QDialog
{
    Q_OBJECT

public:
    explicit Help(QWidget *parent = 0);
    ~Help();

private slots:
    void next();

private:
    Ui::Help *ui;

    int currentMovie;

    const QList<QMovie*> movieList = {
        new QMovie(":/video/change-color.gif", "GIF", this),
        new QMovie(":/video/add-task.gif", "GIF", this),
        new QMovie(":/video/del-task.gif", "GIF", this),
        new QMovie(":/video/drag-files.gif", "GIF", this),
        new QMovie(":/video/export-import.gif", "GIF", this),
        new QMovie(":/video/pin.gif", "GIF", this),
        new QMovie(":/video/mode.gif", "GIF", this)
    };
    const QList<QString> textList = {
        tr("Double-click on a day to set its color."),
        tr("Add a task and set it as repeated optionally."),
        tr("Delete a task just for a day or delete all repeated tasks."),
        tr("Drag files into or out from a day."),
        tr("Export or import all configurations."),
        tr("Drag and pin the calendar."),
        tr("View the calendar in different mode.")
    };
};

#endif // HELP_H
