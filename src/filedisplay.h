#ifndef FILEDISPLAY_H
#define FILEDISPLAY_H

#include <QDate>
#include <QWidget>

namespace Ui {
class FileDisplay;
}

class FileDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit FileDisplay(const QDate &_date, int _index, QWidget *parent);
    ~FileDisplay();

private slots:
    void on_label_2_linkActivated(const QString &link);

signals:
    void requireRefresh();

private:
    Ui::FileDisplay *ui;
    QDate date;
    int index;
};

#endif // FILEDISPLAY_H
