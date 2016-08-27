#ifndef FILEDISPLAY_H
#define FILEDISPLAY_H

#include <QDate>
#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class FileDisplay;
}

/// Display a file dragged in by user
class FileDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit FileDisplay(const QDate &_date, int _index, QWidget *parent);
    ~FileDisplay();

protected:
    bool event(QEvent *event) override;

private slots:
    void startDrag();

    void on_label_2_linkActivated(const QString &link);

signals:
    void requireRefresh();

private:
    Ui::FileDisplay *ui;
    QDate date;
    int index;
};

#endif // FILEDISPLAY_H
