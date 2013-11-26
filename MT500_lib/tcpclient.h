#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>

class TCPClient : public QObject
{
    Q_OBJECT
public:
    explicit TCPClient(QString address, quint16 port = 3154, QObject *parent = 0);

    void write(QByteArray toWrite);

signals:

public slots:

private:

    QTcpSocket *m_connection;
    quint16 m_port;
    QString m_address;

};

#endif // TCPCLIENT_H
