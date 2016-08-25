#include <QDebug>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include "task.h"

Task::Task(QJsonValueRef json, QObject *parent) : QObject(parent)
{
    Q_ASSERT(json.isObject());
    QJsonObject obj = json.toObject();
    baseDate = QDate::fromJulianDay(obj["baseDate"].toInt());
    content = obj["content"].toString();
    repeatType = (RepeatType)(obj["repeatType"].toInt());
    repeatInterval = obj["repeatInterval"].toInt();
    QJsonArray excludeArr = obj["exclude"].toArray();
    for (int i = 0; i < excludeArr.count(); i++)
        exclude.push_back(QDate::fromJulianDay(excludeArr[i].toInt()));
}

Task::Task(const QDate &_baseDate, QObject *parent)
    : QObject(parent),
      baseDate(_baseDate), content(""), repeatType(NONE), repeatInterval(0)
{}

QJsonValue Task::toJson() const
{
    QJsonObject ret;
    ret["baseDate"] = baseDate.toJulianDay();
    ret["content"] = content;
    ret["repeatType"] = repeatType;
    ret["repeatInterval"] = repeatInterval;
    QJsonArray excludeArr;
    for (int i = 0; i < exclude.count(); i++)
        excludeArr.push_back(exclude[i].toJulianDay());
    ret["exclude"] = excludeArr;
    return ret;
}

bool Task::isFor(const QDate &day) const
{
    for (int i = 0; i < exclude.count(); i++)
        if (exclude[i] == day)
            return false;
    switch (repeatInterval)
    {
    case NONE:
        return (baseDate == day);
    case BY_DAY:
        return (baseDate.daysTo(day) % repeatInterval == 0);
    case BY_MONTH:
        return (((baseDate.year() * 12 + baseDate.month()) - (day.year() * 12 + day.month())) % repeatInterval == 0);
    case BY_YEAR:
        return ((baseDate.year() - day.year()) % repeatInterval == 0);
    default:
        Q_ASSERT(false);
    }
}

const QDate &Task::getBaseDate() const
{
    return baseDate;
}

void Task::setContent(const QString &_content)
{
    content = _content;
}

const QString &Task::getContent() const
{
    return content;
}

Task::RepeatType Task::getRepeatType() const
{
    return repeatType;
}

void Task::addExclude(const QDate &day)
{
    exclude.push_back(day);
}
