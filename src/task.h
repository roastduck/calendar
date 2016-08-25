#ifndef TASK_H
#define TASK_H

#include <QDate>
#include <QString>
#include <QObject>
#include <QJsonValue>

/// A task defined by user
class Task : public QObject
{
    Q_OBJECT
public:
    enum RepeatType
    {
        NONE = 0,
        BY_DAY = 1,
        BY_MONTH = 2,
        BY_YEAR = 3
    };

    /// Parse from json
    explicit Task(QJsonValueRef json, QObject *parent);

    /// New task for a day
    explicit Task(QDate _baseDate, QObject *parent);

    /// Output to json
    QJsonValue toJson() const;

    /// Check whether the task should be applied to a day
    bool isFor(QDate day) const;

    QString getContent() const;

private:
    QDate baseDate;

    QString content;

    RepeatType repeatType;
    int repeatInterval;
};

#endif // TASK_H
