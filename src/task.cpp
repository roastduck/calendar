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
}

Task::Task(QDate _baseDate, QObject *parent)
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
    return ret;
}

bool Task::isFor(QDate day) const
{
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

void Task::setContent(QString _content)
{
    content = _content;
}

QString Task::getContent() const
{
    return content;
}
