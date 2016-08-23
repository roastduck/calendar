#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDate>
#include <QColor>
#include <QPoint>
#include <QWidget>
#include <QTranslator>
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

    void initMonth();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_comboBox_activated(int index);
    void on_quitButton_clicked(bool checked);
    void on_previousButton_clicked(bool checked);
    void on_nextButton_clicked(bool checked);
    void on_yearBox_valueChanged(int arg1);
    void on_monthBox_valueChanged(int arg1);
    void on_dayBox_valueChanged(int arg1);

private:
    void alterDisplayedDate(QDate date);

    void clearGrid();

    QWidget *newCell(QWidget *w, QColor c);

    QWidget *dayInMonth(QDate date, bool monthDisplayed);

    Ui::MainWindow *ui;

    QDate displayedDate;

    QPoint dPos;

    QTranslator chinese;
};

#endif // MAINWINDOW_H
