#include <QUrl>
#include <QList>
#include <QFile>
#include <QDebug>
#include <QPalette>
#include <QMimeData>
#include <QGraphicsColorizeEffect>
#include "data.h"
#include "file.h"
#include "tile.h"
#include "ui_tile.h"
#include "mainwindow.h"

Tile::Tile(QColor color, QString title, QList<QWidget*> body, bool isDay, QWidget *parent, const QDate &_today)
    : QWidget(parent),
      ui(new Ui::Tile()),
      hoverEffect(isDay),
      today(_today)
{
    ui->setupUi(this);

    QPalette thisPalette = palette();
    thisPalette.setColor(QPalette::Window, color);
    setPalette(thisPalette);

    ui->title->setText(title);
    ui->title->setAttribute(Qt::WA_TransparentForMouseEvents);

    for (int i = 0; i < body.count(); i++)
    {
        body[i]->setParent(this);
        layout()->addWidget(body[i]);
    }

    setAcceptDrops(isDay);
}

Tile::~Tile()
{
    delete ui;
}

void Tile::highlight()
{
    QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect(this);
    setGraphicsEffect(effect);
}

void Tile::removeHighlight()
{
    setGraphicsEffect(0);
}

bool Tile::event(QEvent *event)
{
    if (MainWindow::getMyInstance()->isPinned())
    {
        event->accept();
        return true;
    }
    return QWidget::event(event);
}

void Tile::dragEnterEvent(QDragEnterEvent *event)
{
    highlight();
    event->acceptProposedAction();
    QWidget::dragEnterEvent(event);
}

void Tile::dragLeaveEvent(QDragLeaveEvent *event)
{
    removeHighlight();
    QWidget::dragLeaveEvent(event);
}

void Tile::dropEvent(QDropEvent *event)
{
    if (! event->mimeData()->hasUrls()) return;
    QList<QUrl> urls = event->mimeData()->urls();
    for (int i = 0; i < urls.count(); i++)
    {
        qDebug() << "received url " << urls[i];
        MainWindow::getMyInstance()->calendarData->addFile(today, urls[i]);
    }
    emit requireRefresh();
    QWidget::dropEvent(event);
}

void Tile::enterEvent(QEvent *event)
{
    if (hoverEffect) highlight();
    QWidget::enterEvent(event);
}

void Tile::leaveEvent(QEvent *event)
{
    if (hoverEffect) removeHighlight();
    QWidget::leaveEvent(event);
}

void Tile::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
        emit onSelected();
    QWidget::mousePressEvent(event);
}

void Tile::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit onSelected();
    QWidget::mouseDoubleClickEvent(event);
}
