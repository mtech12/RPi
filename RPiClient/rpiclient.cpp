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

    connect(m_server, SIGNAL(sigGotData(QByteArray)), this, SLOT(slot_gotData(QByteArray)));
    connect(m_ip, SIGNAL(sig_picTaken ()), this, SLOT(slot_sendPicture()));
    connect(m_cp, SIGNAL (sigSendImage ()), this, SLOT(slot_takePicture()));
    connect(m_cp, SIGNAL (sigRecvTime ()), this, SLOT(slot_gotTime()));

    slot_requestTime ();
    qDebug() << "Time: " << Utilities::getTime (m_cfg[TIMEZONE].toDouble (), "MM/dd/yyyy hh:mm:ss");
}

void RPiClient::slot_sendPicture()
{
    qDebug() << "Sending picture!";
    QString time = Utilities::getTime (m_cfg[TIMEZONE].toDouble (), "yyyyMMddThh:mm:ss");
    QByteArray toSend = m_dataPro->encode(m_ip->loadImage(m_cfg[DEVICE_ID].toString (), time, "/root/test.jpg"), IMAGE_RESPONSE); 
    m_client->write(toSend);
}

void RPiClient::slot_takePicture()
{
    qDebug() << "Taking picture!";
    m_ip->takePicture();
}

void RPiClient::slot_gotData(QByteArray data)
{
    qDebug() << "Got data!";
    m_cp->parseCommand (m_dataPro->decode (data));
}

void RPiClient::slot_requestTime ()
{
    qDebug() << "Requesting time";
    QByteArray toSend = m_dataPro->encode(NULL, SYNC_TIME); 
    m_client->write(toSend);
}

void RPiClient::slot_gotTime ()
{
    qDebug() << "Got time!";
    QString cmd = QString("date %1").arg(m_dataPro->getData ().data ());
    system (cmd.toStdString ().c_str ());
}
