#include "mainwindow.h"
#include "monthmodel.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mModel = new MonthModel(2016, 8);
    ui->tableView->setModel(mModel->getModel());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mModel;
}
