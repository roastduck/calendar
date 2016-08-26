#include <QDebug>
#include <QLabel>
#include <QString>
#include "data.h"
#include "file.h"
#include "html.h"
#include "mainwindow.h"
#include "filedisplay.h"
#include "ui_filedisplay.h"

FileDisplay::FileDisplay(const QDate &_date, int _index, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileDisplay),
    date(_date),
    index(_index)
{
    ui->setupUi(this);
    QString filename = MainWindow::getMyInstance()->calendarData->getFile(date, index)->getFilename();
    if (filename.length() > 10)
        filename = filename.left(7) + "...";
    filename = Html::link("<img src=':icon/file.ico'></img>" + filename);
    ui->label->setText(filename);
}

FileDisplay::~FileDisplay()
{
    delete ui;
}

void FileDisplay::on_label_2_linkActivated(const QString &)
{
    qDebug() << "link clicked";
    MainWindow::getMyInstance()->calendarData->delFile(date, index);
    emit requireRefresh(); // don't use deleteLater because index changed
}
