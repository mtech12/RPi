#ifndef RPICLIENT_H
#define RPICLIENT_H

#include <QObject>
#include <QTimer>
#include <QDebug>

#include "imageprocessor.h"
#include "tcpclient.h"
#include "dataprotocol.h"
#include "tcpserver.h"
#include "utilities.h"
#include "commandparser.h"
#include "commands.h"

class RPiClient : public QObject
{
    Q_OBJECT
public:
    explicit RPiClient(QObject *parent = 0);

signals:

public slots:

    void slotTakePicture ();
    void slotSendPicture ();
    void slotGotData (QByteArray);
    void slotRequestTime ();
    void slotGotTime ();
    void slotResend ();
    void slotRequestResend ();
    void slotSendConfig ();
    void slotReboot ();

private:

    QVariantMap m_cfg;
    ImageProcessor *m_ip;
    TCPClient *m_client;
    TCPServer *m_server;
    DataProtocol *m_dataPro;
    QTimer *m_picTimer;
    CommandParser *m_cp;

};

#endif // RPICLIENT_H
