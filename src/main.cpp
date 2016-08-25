#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow::createInstance();
    MainWindow *w = MainWindow::getMyInstance();
    w->postConstructInit();
    w->setWindowFlags(Qt::FramelessWindowHint);
    w->setAttribute(Qt::WA_TranslucentBackground);
    w->show();

    int ret = app.exec();
    MainWindow::destroyInstance();
    return ret;
}
