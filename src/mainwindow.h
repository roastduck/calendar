#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QRect>
#include <QDate>
#include <QEvent>
#include <QColor>
#include <QPoint>
#include <QWidget>
#include <QLayout>
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

    /// Initialize a month display
    void initMonth();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void promptTileBar(QWidget *tile);

    void on_comboBox_activated(int index);
    void on_quitButton_clicked(bool checked);
    void on_previousButton_clicked(bool checked);
    void on_nextButton_clicked(bool checked);
    void on_yearBox_valueChanged(int arg1);
    void on_monthBox_valueChanged(int arg1);
    void on_dayBox_valueChanged(int arg1);

private:
    /// Display another date
    void alterDisplayedDate(QDate date);

    /// Clear all cells in the grid
    void clearGrid();

    /// Generates a new grid cell
    /// @param mouseBehavior : true means response to mouse events
    QWidget *newCell(QWidget *w, QColor c, bool mouseBehavior = false);

    /// Generates a cell for a day in a month display
    QWidget *dayInMonth(QDate date, bool monthDisplayed);

    Ui::MainWindow *ui;

    /// date displayed in the main window
    QDate displayedDate;

    /// Original pos for moving the window
    QPoint dPos;

    QTranslator chinese;
};

#endif // MAINWINDOW_H
