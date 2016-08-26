#ifndef DATA_H
#define DATA_H

#include <QUrl>
#include <QMap>
#include <QList>
#include <QDate>
#include <QColor>
#include <QString>
#include <QObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValueRef>

class Task;
class File;

/// Manage all user data and save it as JSON format
class Data : public QObject
{
    Q_OBJECT
public:
    /// Retrieve data from file
    explicit Data(QObject *parent);

    /// Save data to file
    ~Data();

    void setDayColor(const QDate &day, const QColor &color);
    QColor getDayColor(const QDate &day) const;

    void setChinese(bool chinese);
    bool isChinese() const;

    /// Initialize a task for a day
    void addTask(const QDate &day);

    /// Delete a task
    void delTask(int index);

    /// Return indices of tasks for a day
    QList<int> findTask(const QDate &day) const;

    /// Get a task by index
    const Task *taskAt(int index) const;
    Task *taskAt(int index);

    /// Attach a file to a day
    /**
     * @return : index
     */
    int addFile(const QDate &date, const QUrl &path);
    QList<File*> getFile(const QDate &date);
    File *getFile(const QDate &date, int index);
    void delFile(const QDate &date, int index);

    /// File to save data
    static constexpr const char *saveFile = "savedcalendar.json";

private:
    const QColor defaultDayColor= QColor(0xE0, 0xFF, 0x85, 0xD0);

    QJsonObject data;
    QList<Task*> tasks;
    QMap< QDate, QList<File*> > files;
};

#endif // DATA_H
