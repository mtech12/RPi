#ifndef UTILITIES_H
#define UTILITIES_H

#include <QFile>
#include <QVariant>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QDateTime>

#define DEVICE_ID       	"id"
#define DEVICE_LABEL    	"label"
#define IMAGE_INTERVAL  	"imageInterval"
#define TIMEZONE        	"timezone"
#define SERVER_IP		"serverip"
#define CLIENT_IP		"clientip"
#define IMAGE_DIRECTORY		"imageDirectory"

class Utilities : public QObject
{
    Q_OBJECT
public:
    Utilities(QObject *parent = 0);
    static QVariantMap getConfig (const QString & file);
    static QString getTime (const double & offset, const QString & format);

signals:

public slots:

};

#endif // UTILITIES_H
