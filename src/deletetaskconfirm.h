#ifndef DELETETASKCONFIRM_H
#define DELETETASKCONFIRM_H

#include <QDialog>

namespace Ui {
class DeleteTaskConfirm;
}

class DeleteTaskConfirm : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteTaskConfirm(bool _isRepeatTask, QWidget *parent = 0);
    ~DeleteTaskConfirm();

signals:
    void cancel(QDialog *dialog);
    void single(QDialog *dialog);
    void whole(QDialog *dialog);

private slots:
    void on_pushButton_clicked(bool checked);
    void on_pushButton_2_clicked(bool checked);
    void on_pushButton_3_clicked(bool checked);

private:
    Ui::DeleteTaskConfirm *ui;

    bool isRepeatTask;
};

#endif // DELETETASKCONFIRM_H
