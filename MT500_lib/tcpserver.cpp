#include "tcpserver.h"

TCPServer::TCPServer(quint16 port,QObject *parent) :
    QObject(parent)
{
    listen (port);
}

void TCPServer::listen (quint16 port)
{
    m_server = new QTcpServer ();
    if(!m_server->listen (QHostAddress::Any, port)) qDebug() << "Failed to start listening...";
    else {
        qDebug() << QString("The server is listening on port %1").arg(m_server->serverPort ());
        connect(m_server, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
    }
}

void TCPServer::slotNewConnection ()
{
    qDebug() << "Got a new connection!!!!";
    m_clientConnection = m_server->nextPendingConnection();
    //Make sure the connection is deleted when it disconnects
    connect (m_clientConnection, SIGNAL(disconnected()), this, SLOT(slotDoneRecv()));
    connect (m_clientConnection, SIGNAL(readyRead()), this, SLOT(slotReadData()));
}

void TCPServer::slotReadData ()
{
    m_data.append(m_clientConnection->readAll ());
}

QByteArray TCPServer::getData ()
{
    return m_data;
}

void TCPServer::slotDoneRecv ()
{
    emit sigGotData(m_data);
    m_clientConnection->deleteLater();
    m_data.clear();
}
