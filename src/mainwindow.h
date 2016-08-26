#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMap>
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

class Data;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    static void createInstance();
    static MainWindow *getMyInstance();
    static void destroyInstance();

    /// Do some initialization that cannot be put into constructor
    void postConstructInit();

    /// Whether to not response to mouse event
    bool isPinned() const { return pinned; }

private:
    explicit MainWindow(QWidget *parent = 0);
    MainWindow(const MainWindow &) = delete;
    ~MainWindow();

public slots:
    /// Initialize or renew the main grid display
    void init();

public:
    /// All data set by user
    Data *calendarData;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    void promptTaskBar(QWidget *task, int taskIndex, QDate today);

private slots:
    void promptTileBar(QWidget *tile);

    void on_comboBox_activated(int index);
    void on_quitButton_clicked(bool checked);
    void on_previousButton_clicked(bool checked);
    void on_nextButton_clicked(bool checked);
    void on_yearBox_valueChanged(int arg1);
    void on_monthBox_valueChanged(int arg1);
    void on_dayBox_valueChanged(int arg1);
    void on_exportButton_clicked(bool checked);
    void on_importButton_clicked(bool checked);
    void on_pinButton_clicked(bool checked);
    void on_dragSwitchButton_clicked(bool checked);

    void on_dragSwitchButton_toggled(bool checked);

private:
    /// Initialize a month display
    void initMonth();

    /// Display another date
    void alterDisplayedDate(QDate date);

    /// Clear all cells in the grid
    void clearGrid();

    /// Generates a cell for a day in a month display
    QWidget *dayInMonth(QDate date, bool monthDisplayed);

    Ui::MainWindow *ui;

    /// date displayed in the main window
    QDate displayedDate;

    /// is dragging window
    bool isDragging;
    /// Original pos for moving the window
    QPoint dPos;

    /// What wiget refers to what date
    QMap<QWidget*, QDate> widgetToDate;

    QTranslator chinese;

    /// Prevent recursive calling
    bool changingDate;

    /// The grid not reveiving mouse event
    bool pinned;

    static MainWindow *myInstance;
};

#endif // MAINWINDOW_H
