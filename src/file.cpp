#include <QFile>
#include <QJsonObject>
#include "file.h"

File::File(QJsonValueRef json, QObject *parent) : QObject(parent)
{
    Q_ASSERT(json.isObject());
    QJsonObject obj = json.toObject();
    Q_ASSERT(obj["filename"].isString());
    filename = obj["filename"].toString();
    Q_ASSERT(obj["base64"].isString());
    base64 = obj["base64"].toString();
}

File::File(const QUrl &path, QObject *parent) : QObject(parent)
{
    filename = path.fileName();
    QFile file(path.toLocalFile());
    Q_ASSERT(file.open(QIODevice::ReadOnly));
    base64 = file.readAll().toBase64();
}

QJsonValue File::toJson() const
{
    QJsonObject obj;
    obj["filename"] = filename;
    obj["base64"] = base64;
    return obj;
}

const QString &File::getFilename() const
{
    return filename;
}
