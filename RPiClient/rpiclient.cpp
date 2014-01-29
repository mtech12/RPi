#include "rpiclient.h"

RPiClient::RPiClient(QObject *parent) :
    QObject(parent)
{

    // Get configuration
    m_cfg = Utilities::getConfig ("config.mts");

    m_ip = new ImageProcessor ();
    m_client = new TCPClient (m_cfg[SERVER_IP].toString ());
    m_server = new TCPServer ();
    m_cp = new CommandParser ();
    m_dataPro = new DataProtocol ();

    connect(m_server, SIGNAL(sigGotData(QByteArray)), this, SLOT(slotGotData(QByteArray)));
    connect(m_ip, SIGNAL(sig_picTaken ()), this, SLOT(slotSendPicture()));
    connect(m_cp, SIGNAL (sigSendImage ()), this, SLOT(slotTakePicture()));
    connect(m_cp, SIGNAL (sigRecvTime ()), this, SLOT(slotGotTime()));
    connect(m_cp, SIGNAL(sigCRCMismatch()), this, SLOT(slotRequestResend ()));
    connect(m_cp, SIGNAL(sigResend()), this, SLOT(slotResend ()));
    connect(m_cp, SIGNAL(sigSendCfg()), this, SLOT(slotSendConfig ()));
    connect(m_cp, SIGNAL(sigReboot()), this, SLOT(slotReboot ()));

    slotRequestTime ();
    qDebug() << "Time: " << Utilities::getTime (m_cfg[TIMEZONE].toDouble (), "MM/dd/yyyy hh:mm:ss");
}

void RPiClient::slotSendPicture()
{
    qDebug() << "Sending picture!";
    QString time = Utilities::getTime (m_cfg[TIMEZONE].toDouble (), "yyyyMMddThh:mm:ss");
    QByteArray toSend = m_dataPro->encode(m_ip->loadImage(m_cfg[DEVICE_ID].toString (), time, "/root/test.jpg"), IMAGE_RESPONSE); 
    m_client->write(toSend);
}

void RPiClient::slotTakePicture()
{
    qDebug() << "Taking picture!";
    m_ip->takePicture();
}

void RPiClient::slotGotData(QByteArray data)
{
    qDebug() << "Got data!";
    m_cp->parseCommand (m_dataPro->decode (data));
}

void RPiClient::slotRequestTime ()
{
    qDebug() << "Requesting time";
    QByteArray toSend = m_dataPro->encode(NULL, SYNC_TIME); 
    m_client->write(toSend);
}

void RPiClient::slotGotTime ()
{
    qDebug() << "Got time!";
    QString cmd = QString("date %1").arg(m_dataPro->getData ().data ());
    system (cmd.toStdString ().c_str ());
}

void RPiClient::slotRequestResend ()
{
    qDebug () << "CRC Mismatch --- requesting resend of last message";
    m_client->write (m_dataPro->encode (NULL, RESEND));
}

void RPiClient::slotResend ()
{
    //
    // TODO
    // If retries are exceeded how do we reset it?
    //
    static int retries = 0;
    if( retries < m_cfg[RESEND_LIMIT].toInt () ) {
        qDebug() << "Resending previous message...";
        m_client->resend ();
        retries++;
    }
    else retries = 0;
}

void RPiClient::slotSendConfig ()
{
    QString configStr = Utilities::encodeCfg (m_cfg);
    m_client->write (m_dataPro->encode (configStr.toUtf8 (), CFG_RESPONSE)); 
}

void RPiClient::slotReboot ()
{
    qDebug() << "Rebooting...";
    system ("reboot");
}
