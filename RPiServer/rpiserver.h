#ifndef RPISERVER_H
#define RPISERVER_H

#include <QObject>
#include <QTimer>
#include <QDebug>

#include "tcpserver.h"
#include "imageprocessor.h"
#include "tcpclient.h"
#include "dataprotocol.h"
#include "commandparser.h"
#include "utilities.h"
#include "commands.h"

class RPiServer : public QObject
{
    Q_OBJECT
public:
    explicit RPiServer(QObject *parent = 0);

signals:

public slots:

    void slotGotData(QByteArray data);
    void slotSendCommand ();
    void slotRecvImage ();
    void slotSendTime ();

private:

    QVariantMap m_cfg;
    TCPServer *m_server;
    ImageProcessor *m_ip;
    TCPClient *m_client;
    QTimer *m_cmdTimer;
    DataProtocol *m_dataPro;
    CommandParser *m_cp;

};

#endif // RPISERVER_H
