#include <QFile>
#include <QJsonDocument>
#include "data.h"

Data::Data(QObject *parent) : QObject(parent)
{
    QFile file(saveFile);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        data = QJsonDocument::fromJson(file.readAll()).object();
    else
        data = QJsonObject();
}

Data::~Data()
{
    QFile file(saveFile);
    Q_ASSERT(file.open(QIODevice::WriteOnly | QIODevice::Text));
    file.write(QJsonDocument(data).toJson());
}

void Data::setDayColor(QDate day, QColor color)
{
    QJsonObject dayColor = (data["dayColor"].isObject() ? data["dayColor"].toObject() : QJsonObject());
    dayColor[QString::number(day.toJulianDay())] =
        QJsonArray({ color.red(), color.green(), color.blue(), color.alpha() });
    data["dayColor"] = dayColor;
}

QColor Data::getDayColor(QDate day) const
{
    QJsonObject dayColor = (data["dayColor"].isObject() ? data["dayColor"].toObject() : QJsonObject());
    QJsonValueRef element = dayColor[QString::number(day.toJulianDay())];
    if (element.isArray())
    {
        QJsonArray arr = element.toArray();
        return QColor(arr[0].toInt(), arr[1].toInt(), arr[2].toInt(), arr[3].toInt());
    }
    return defaultDayColor;
}
