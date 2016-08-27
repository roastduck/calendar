#include <QDebug>
#include <QDialogButtonBox>
#include "help.h"
#include "ui_help.h"

Help::Help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Help),
    currentMovie(-1)
{
    ui->setupUi(this);
    next();

    ui->buttonBox->addButton(tr("Close"), QDialogButtonBox::RejectRole);
    ui->buttonBox->addButton(tr("Next"), QDialogButtonBox::AcceptRole);
    disconnect(ui->buttonBox, 0, 0, 0);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(next()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

Help::~Help()
{
    delete ui;
}

void Help::next()
{
    currentMovie++;
    qDebug() << "current Movie = " << currentMovie;
    if (currentMovie == movieList.count())
    {
        accept();
        return;
    }
    ui->label->setMovie(movieList[currentMovie]);
    movieList[currentMovie]->start();
    ui->text->setText(textList[currentMovie]);
}
