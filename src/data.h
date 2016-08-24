#ifndef DATA_H
#define DATA_H

#include <QDate>
#include <QColor>
#include <QString>
#include <QObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

class Data : public QObject
{
    Q_OBJECT
public:
    explicit Data(QObject *parent = 0);
    ~Data();

    void setDayColor(QDate day, QColor color);
    QColor getDayColor(QDate day) const;

private:
    const QString saveFile = "savedcalendar.json";

    const QColor defaultDayColor= QColor(0xE0, 0xFF, 0x85, 0xD0);

    QJsonObject data;
};

#endif // DATA_H
