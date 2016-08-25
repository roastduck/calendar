#include "deletetaskconfirm.h"
#include "ui_deletetaskconfirm.h"

DeleteTaskConfirm::DeleteTaskConfirm(bool _isRepeatTask, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteTaskConfirm),
    isRepeatTask(_isRepeatTask)
{
    ui->setupUi(this);
    if (isRepeatTask)
    {
        ui->pushButton_2->hide();
        ui->pushButton_3->setText(tr("Yes"));
        ui->pushButton_3->setToolTip("");
    }
}

DeleteTaskConfirm::~DeleteTaskConfirm()
{
    delete ui;
}

void DeleteTaskConfirm::on_pushButton_clicked(bool)
{
    emit cancel(this);
}

void DeleteTaskConfirm::on_pushButton_2_clicked(bool)
{
    emit single(this);
}

void DeleteTaskConfirm::on_pushButton_3_clicked(bool)
{
    emit whole(this);
}
