#ifndef TASKDISPLAY_H
#define TASKDISPLAY_H

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
    explicit TaskDisplay(int _index, bool _hoverEffect, QWidget *parent);
    ~TaskDisplay();

    void enableEditor();

    /// Get content in the editor
    QString getContent() const;

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    void onSelected(QWidget *anchor, int taskIndex);

private:
    Ui::TaskDisplay *ui;

    int index;

    bool hoverEffect;
};

#endif // TASKDISPLAY_H
