#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDate>
#include <QWidget>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void clearGrid();

    void initMonth(int year, int month);

    QWidget *dayInMonth(QDate date, bool monthDisplayed);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
