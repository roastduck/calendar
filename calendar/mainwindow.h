#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDate>
#include <QColor>
#include <QPoint>
#include <QWidget>
#include <QMainWindow>
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initMonth(int year, int month);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_quitButton_released();

private:
    void clearGrid();

    QWidget *newCell(QWidget *w, QColor c);

    QWidget *dayInMonth(QDate date, bool monthDisplayed);

    Ui::MainWindow *ui;

    QPoint dPos;
};

#endif // MAINWINDOW_H
