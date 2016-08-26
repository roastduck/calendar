#ifndef FILE_H
#define FILE_H

#include <QUrl>
#include <QString>
#include <QObject>
#include <QJsonValue>
#include <QJsonValueRef>

class File : public QObject
{
    Q_OBJECT
public:
    explicit File(QJsonValueRef json, QObject *parent);
    explicit File(const QUrl &path, QObject *parent);

    QJsonValue toJson() const;

    const QString &getFilename() const;

private:
    QString filename, base64;
};

#endif // FILE_H
