#ifndef DATA_H
#define DATA_H

#include <QList>
#include <QDate>
#include <QColor>
#include <QString>
#include <QObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

class Task;

class Data : public QObject
{
    Q_OBJECT
public:
    /// Retrieve data from file
    explicit Data(QObject *parent);

    /// Save data to file
    ~Data();

    void setDayColor(QDate day, QColor color);
    QColor getDayColor(QDate day) const;

    /// Initialize a task for a day
    void addTask(QDate day);

    /// Return indices of tasks for a day
    QList<int> findTask(QDate day) const;

    /// Get a task by index
    const Task *taskAt(int index) const;
    Task *taskAt(int index);

private:
    /// File to save data
    const QString saveFile = "savedcalendar.json";

    const QColor defaultDayColor= QColor(0xE0, 0xFF, 0x85, 0xD0);

    QJsonObject data;
    QList<Task*> tasks;
};

#endif // DATA_H
