#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include "data.h"
#include "task.h"

Data::Data(QObject *parent) : QObject(parent)
{
    QFile file(saveFile);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        data = QJsonDocument::fromJson(file.readAll()).object();
    else
        data = QJsonObject();

    QJsonArray tasksArr = data["tasks"].toArray();
    tasks.reserve(tasksArr.size());
    for (int i = 0; i < tasksArr.size(); i++)
        tasks.push_back(new Task(tasksArr[i], this));
}

Data::~Data()
{
    QJsonArray taskArr;
    for (int i = 0; i < tasks.size(); i++)
        taskArr.push_back(tasks[i]->toJson());
    data["tasks"] = taskArr;

    QFile file(saveFile);
    Q_ASSERT(file.open(QIODevice::WriteOnly | QIODevice::Text));
    file.write(QJsonDocument(data).toJson());
}

void Data::setDayColor(QDate day, QColor color)
{
    QJsonObject dayColor = data["dayColor"].toObject();
    dayColor[QString::number(day.toJulianDay())] =
        QJsonArray({ color.red(), color.green(), color.blue(), color.alpha() });
    data["dayColor"] = dayColor;
}

QColor Data::getDayColor(QDate day) const
{
    QJsonObject dayColor = data["dayColor"].toObject();
    QJsonValueRef element = dayColor[QString::number(day.toJulianDay())];
    if (element.isArray())
    {
        QJsonArray arr = element.toArray();
        return QColor(arr[0].toInt(), arr[1].toInt(), arr[2].toInt(), arr[3].toInt());
    }
    return defaultDayColor;
}

void Data::addTask(QDate day)
{
    tasks.push_back(new Task(day, this));
}

QList<int> Data::findTask(QDate day) const
{
    QList<int> ret;
    for (int i = 0; i < tasks.size(); i++)
        if (tasks[i]->isFor(day))
            ret.push_back(i);
    return ret;
}

const Task *Data::taskAt(int index) const
{
    return tasks[index];
}

Task *Data::taskAt(int index)
{
    return tasks[index];
}
