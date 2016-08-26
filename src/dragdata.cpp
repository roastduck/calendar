#include <QDir>
#include <QUrl>
#include <QFile>
#include <QDebug>
#include <QIODevice>
#include <QFileInfo>
#include <QByteArray>
#include "dragdata.h"

DragData::DragData(const QString &_filename, const QString _base64)
    : fileCreated(false), filename(_filename), base64(_base64)
{}

QStringList DragData::formats() const
{
    return { "text/uri-list" };
}

bool DragData::hasFormat(const QString &mimeType) const
{
    return (mimeType == "text/uri-list");
}

QVariant DragData::retrieveData(const QString &mimetype, QVariant::Type) const
{
    if (mimetype != "text/uri-list") return QVariant();
    if (! fileCreated)
    {
        if (! QFileInfo("tmp").isDir())
            Q_ASSERT(QDir().mkdir("tmp"));

        QFile file("tmp/" + filename);
        Q_ASSERT(file.open(QIODevice::WriteOnly));
        file.write(QByteArray::fromBase64(base64.toLatin1()));
        file.close();
        fileCreated = true;
    }
    // both returning url and url list are ok
    QUrl url(QUrl::fromLocalFile(QFileInfo("tmp/" + filename).absoluteFilePath()));
    qDebug() << "sent " << url;
    return url;
}
