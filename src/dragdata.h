#ifndef DRAGDATA_H
#define DRAGDATA_H

#include <QString>
#include <QVariant>
#include <QMimeData>
#include <QStringList>

/// Create a file and return its url when requested
class DragData : public QMimeData
{
    Q_OBJECT
public:
    DragData(const QString &_filename, const QString _base64);

    QStringList formats() const override;
    bool hasFormat(const QString &mimeType) const override;

protected:
    QVariant retrieveData(const QString &mimetype, QVariant::Type preferredType) const override;

private:
    /// Only create temporary file once
    mutable bool fileCreated;

    QString filename;

    /// file content in Base64
    QString base64;
};

#endif // DRAGDATA_H
