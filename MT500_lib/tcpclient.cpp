#include "tcpclient.h"

TCPClient::TCPClient(QString address,quint16 port,QObject *parent) :
    QObject(parent)
{
    m_connection = new QTcpSocket ();
    m_address = address;
    m_port = port;
}

void TCPClient::write(QByteArray toWrite)
{
    m_connection->connectToHost(QHostAddress(m_address), m_port);
    m_connection->waitForConnected();
    m_connection->write(toWrite);
    m_connection->waitForBytesWritten();
    m_connection->disconnectFromHost();
}

