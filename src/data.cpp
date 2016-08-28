#include <QFile>
#include <QPair>
#include <QDebug>
#include <QIODevice>
#include <QJsonDocument>
#include "data.h"
#include "task.h"
#include "file.h"

Data::Data(QObject *parent) : QObject(parent)
{
    QFile file(saveFile);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        data = QJsonDocument::fromJson(file.readAll()).object();
        file.close();
    } else
        data = QJsonObject();

    QJsonArray tasksArr = data["tasks"].toArray();
    tasks.reserve(tasksArr.size());
    for (int i = 0; i < tasksArr.size(); i++)
        tasks.push_back(new Task(tasksArr[i], this));

    QJsonObject filesObj = data["files"].toObject();
    for (auto iter = filesObj.begin(); iter != filesObj.end(); iter++)
    {
        QJsonArray filesArr = iter.value().toArray();
        QList<File*> target;
        target.reserve(filesArr.size());
        for (int i = 0; i < filesArr.size(); i++)
            target.push_back(new File(filesArr[i], this));
        files[QDate::fromJulianDay(iter.key().toInt())] = target;
    }
}

Data::~Data()
{
    QJsonArray taskArr;
    for (int i = 0; i < tasks.size(); i++)
        taskArr.push_back(tasks[i]->toJson());
    data["tasks"] = taskArr;

    QJsonObject filesObj;
    for (auto iter = files.begin(); iter != files.end(); iter++)
    {
        QJsonArray filesArr;
        const QList<File*> &target = iter.value();
        for (int i = 0; i < target.size(); i++)
            filesArr.push_back(target[i]->toJson());
        filesObj[QString::number(iter.key().toJulianDay())] = filesArr;
    }
    data["files"] = filesObj;

    QFile file(saveFile);
    bool success = file.open(QIODevice::WriteOnly | QIODevice::Text);
    Q_ASSERT(success);
    file.write(QJsonDocument(data).toJson());
    file.close();
}

void Data::setDayColor(const QDate &day, const QColor &color)
{
    QJsonObject dayColor = data["dayColor"].toObject();
    dayColor[QString::number(day.toJulianDay())] =
        QJsonArray({ color.red(), color.green(), color.blue(), color.alpha() });
    data["dayColor"] = dayColor;
}

QColor Data::getDayColor(const QDate &day) const
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

void Data::setChinese(bool chinese)
{
    data["chinese"] = chinese;
}

bool Data::isChinese() const
{
    return data["chinese"].toBool();
}

void Data::disableDrag(bool disable)
{
    data["disableDrag"] = disable;
}

bool Data::dragDisabled() const
{
    return data["disableDrag"].toBool();
}

void Data::addTask(const QDate &day)
{
    tasks.push_back(new Task(day, this));
}

void Data::delTask(int index)
{
    tasks.removeAt(index);
}

QList<int> Data::findTask(const QDate &day) const
{
    QList<int> ret;
    for (int i = 0; i < tasks.size(); i++)
        if (tasks[i]->isFor(day))
            ret.push_back(i);
    return ret;
}

const Task *Data::taskAt(int index) const
{
    qDebug() << "required task " << index;
    return tasks[index];
}

Task *Data::taskAt(int index)
{
    return tasks[index];
}

const QList<Task*> &Data::allTasks() const
{
    return tasks;
}

int Data::addFile(const QDate &date, const QUrl &path)
{
    files[date].push_back(new File(path, this));
    return files[date].size() - 1;
}

QList<File*> Data::getFile(const QDate &date)
{
    if (! files.count(date)) return {};
    return files[date];
}

File *Data::getFile(const QDate &date, int index)
{
    Q_ASSERT(index >= 0 && index < files[date].size());
    return files[date][index];
}

void Data::delFile(const QDate &date, int index)
{
    Q_ASSERT(index >= 0 && index < files[date].size());
    files[date].removeAt(index);
    if (files[date].empty())
    {
        qDebug() << "cleaned empty array";
        files.remove(date);
    }
}

const QMap< QDate, QList<File*> > &Data::allFiles() const
{
    return files;
}
