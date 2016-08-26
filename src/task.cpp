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
    Q_ASSERT((int)repeatType >= 0 && (int)repeatType <= 3);
    repeatInterval = obj["repeatInterval"].toInt();
    Q_ASSERT(repeatInterval >= 1);
    QJsonArray excludeArr = obj["exclude"].toArray();
    for (int i = 0; i < excludeArr.count(); i++)
        exclude.push_back(QDate::fromJulianDay(excludeArr[i].toInt()));
}

Task::Task(const QDate &_baseDate, QObject *parent)
    : QObject(parent),
      baseDate(_baseDate), content(""), repeatType(NONE), repeatInterval(1)
{}

QJsonValue Task::toJson() const
{
    QJsonObject ret;
    ret["baseDate"] = baseDate.toJulianDay();
    ret["content"] = content;
    Q_ASSERT((int)repeatType >= 0 && (int)repeatType <= 3);
    ret["repeatType"] = repeatType;
    Q_ASSERT(repeatInterval >= 1);
    ret["repeatInterval"] = repeatInterval;
    QJsonArray excludeArr;
    for (int i = 0; i < exclude.count(); i++)
        excludeArr.push_back(exclude[i].toJulianDay());
    ret["exclude"] = excludeArr;
    return ret;
}

bool Task::isFor(const QDate &day) const
{
    if (day < baseDate) return false;
    for (int i = 0; i < exclude.count(); i++)
        if (exclude[i] == day)
            return false;
    switch (repeatType)
    {
    case NONE:
        return (baseDate == day);
    case BY_DAY:
        return (baseDate.daysTo(day) % repeatInterval == 0);
    case BY_MONTH:
        return (baseDate.day() == day.day() && ((baseDate.year() * 12 + baseDate.month()) - (day.year() * 12 + day.month())) % repeatInterval == 0);
    case BY_YEAR:
        return (baseDate.day() == day.day() && baseDate.month() == day.month() && (baseDate.year() - day.year()) % repeatInterval == 0);
    default:
        qDebug() << "repeatInterval = " << repeatInterval;
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
    Q_ASSERT((int)repeatType >= 0 && (int)repeatType <= 3);
    return repeatType;
}

void Task::setRepeatType(RepeatType t)
{
    Q_ASSERT((int)repeatType >= 0 && (int)repeatType <= 3);
    repeatType = t;
}

int Task::getRepeatInterval() const
{
    return repeatInterval;
}

void Task::setRepeatInterval(int interval)
{
    repeatInterval = interval;
}

void Task::addExclude(const QDate &day)
{
    exclude.push_back(day);
}
