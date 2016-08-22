#include <QDate>
#include <QList>
#include <QString>
#include <QStandardItem>
#include "monthmodel.h"

MonthModel::MonthModel(int year, int month)
{
    mModel->setHorizontalHeaderItem(0, new QStandardItem(tr("Mon")));
    mModel->setHorizontalHeaderItem(1, new QStandardItem(tr("Tue")));
    mModel->setHorizontalHeaderItem(2, new QStandardItem(tr("Wed")));
    mModel->setHorizontalHeaderItem(3, new QStandardItem(tr("Thu")));
    mModel->setHorizontalHeaderItem(4, new QStandardItem(tr("Fri")));
    mModel->setHorizontalHeaderItem(5, new QStandardItem(tr("Sat")));
    mModel->setHorizontalHeaderItem(6, new QStandardItem(tr("Sun")));

    QDate iter(year, month, 1);
    while (iter.dayOfWeek() != 1) iter = iter.addDays(-1);
    QList<QStandardItem*> row;
    for (; iter.month() == month || iter.dayOfWeek() != 1; iter = iter.addDays(1))
    {
        row.append(new QStandardItem(QString::number(iter.day())));
        if (row.count() == 7)
        {
            mModel->appendRow(row);
            mModel->setVerticalHeaderItem(mModel->rowCount() - 1, new QStandardItem(QString::number(iter.weekNumber())));
            row.clear();
        }
    }
    if (!row.empty())
        mModel->appendRow(row);
}
