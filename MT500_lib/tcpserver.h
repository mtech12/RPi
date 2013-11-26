#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class TCPServer : public QObject
{
    Q_OBJECT
public:
    explicit TCPServer(quint16 port = 3154, QObject *parent = 0);

    void listen (quint16 port);

    QByteArray getData ();

signals:

    void sigGotData(QByteArray data);

public slots:

    void slotNewConnection ();
    void slotReadData ();
    void slotDoneRecv ();

private:

    QTcpServer *m_server;
    QTcpSocket *m_clientConnection;
    QByteArray m_data;

};

#endif // TCPSERVER_H
