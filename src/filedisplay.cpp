#include <QDrag>
#include <QDebug>
#include <QLabel>
#include <QString>
#include <QPixmap>
#include "data.h"
#include "file.h"
#include "html.h"
#include "dragdata.h"
#include "mainwindow.h"
#include "filedisplay.h"
#include "labelwithclick.h"
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
    QLabel *label = new LabelWithClick(filename, ui->forLabel);
    ui->forLabel->layout()->addWidget(label);
    connect(label, SIGNAL(clicked()), this, SLOT(startDrag()));
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

void FileDisplay::startDrag()
{
    if (MainWindow::getMyInstance()->calendarData->dragDisabled()) return;
    File *file = MainWindow::getMyInstance()->calendarData->getFile(date, index);
    DragData *dragData = new DragData(file->getFilename(), file->getBase64());
    QDrag *drag = new QDrag(this);
    drag->setMimeData(dragData);
    drag->setPixmap(QPixmap(":/icon/file.ico"));
    drag->exec(Qt::MoveAction);
}
