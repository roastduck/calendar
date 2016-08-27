#ifndef TASKDISPLAY_H
#define TASKDISPLAY_H

#include <QDate>
#include <QEvent>
#include <QString>
#include <QWidget>

namespace Ui {
class TaskDisplay;
}

/// Display and edit a task
class TaskDisplay : public QWidget
{
    Q_OBJECT

public:
    /**
     * @param _index : task index
     * @param _hoverEffect : whether to highlight on hover event and recieve double-click to prompt menu
     */
    explicit TaskDisplay(int _index, bool _hoverEffect, QDate _today, QWidget *parent);
    ~TaskDisplay();

    void enableEditor();

    /// Get content in the editor
    QString getContent() const;

protected:
    bool event(QEvent *event);

    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    void onSelected(QWidget *anchor, int taskIndex, QDate today);

private:
    Ui::TaskDisplay *ui;

    int index;

    bool hoverEffect;

    QDate today;
};

#endif // TASKDISPLAY_H
