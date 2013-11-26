#include "utilities.h"

Utilities::Utilities(QObject *parent) :
    QObject(parent)
{
}

QVariantMap Utilities::getConfig (const QString & file)
{
    QFile in (file);
    QString contents;
    if (in.open (QIODevice::ReadOnly) == true) {
        contents = in.readAll ();
        in.close ();
    }

    qDebug() << contents;

    QJsonDocument doc = QJsonDocument::fromJson (contents.toUtf8 ());
    QJsonObject obj = doc.object ();
    return obj.toVariantMap ();
}

QString Utilities::getTime (const double & offset, const QString & format)
{
    QDateTime now = QDateTime::currentDateTime ();
    uint unixTimestamp = now.toTime_t ();
    unixTimestamp += offset * 60 * 60; //Take offset in hours and convert to seconds and add to timestamp
    QDateTime newTime = QDateTime::fromTime_t (unixTimestamp);
    return newTime.toString (format);
}
