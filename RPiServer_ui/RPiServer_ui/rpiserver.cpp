#include "rpiserver.h"
#include "ui_rpiserver.h"
#include <QPixmap>


RPiServer::RPiServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RPiServer)
{
    ui->setupUi(this);
    m_cfg = Utilities::getConfig ("config.mts");
    qDebug() << m_cfg[IMAGE_INTERVAL].toString ();

    m_server = new TCPServer ();
    m_ip = new ImageProcessor ();
    m_dataPro = new DataProtocol ();
    m_client = new TCPClient (m_cfg[CLIENT_IP].toString ());
    m_cp = new CommandParser ();

    connect(m_server, SIGNAL(sigGotData(QByteArray)), this, SLOT(slotGotData(QByteArray)));
    //
    // Slots to respond to Command Parser signals
    //
    connect(m_cp, SIGNAL(sigRecvImage()), this, SLOT(slotRecvImage ()));
    connect(m_cp, SIGNAL(sigSendTime()), this, SLOT(slotSendTime ()));
    connect(m_cp, SIGNAL(sigCRCMismatch()), this, SLOT(slotRequestResend ()));
    connect(m_cp, SIGNAL(sigResend()), this, SLOT(slotResend ()));
    connect(m_cp, SIGNAL(sigRecvCfg()), this, SLOT(slotRecvConfig ()));


    QPixmap mypix ("/home/ubuntu/Desktop/tux.png");
    ui->testLbl->setPixmap(mypix);
}

RPiServer::~RPiServer()
{
    delete ui;
}

void RPiServer::slotGotData (QByteArray data)
{
    qDebug() << "Got Data!";
    m_cp->parseCommand (m_dataPro->decode (data));
}

void RPiServer::slotSendCommand (unsigned char command)
{
    qDebug() << "Sending message...";
    QByteArray msg = m_dataPro->encode(NULL, command);
    m_client->write (msg);
}

void RPiServer::slotRecvImage ()
{
    qDebug() << "Saving Image!";
    m_ip->saveImage(m_dataPro->getData (), m_cfg[IMAGE_DIRECTORY].toString ());
}

void RPiServer::slotSendTime ()
{
    qDebug() << "Sending time!";
    QDateTime now = QDateTime::currentDateTimeUtc ();
    QByteArray toSend = now.toString("MMddhhmmyyyy.ss").toStdString ().c_str ();
    m_client->write (m_dataPro->encode (toSend, TIME_RESPONSE));
}

void RPiServer::slotRequestResend ()
{
    qDebug () << "CRC Mismatch --- requesting resend of last message";
    m_client->write (m_dataPro->encode (NULL, RESEND));
}

void RPiServer::slotResend ()
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

void RPiServer::slotRequestConfig ()
{
    QByteArray msg = m_dataPro->encode(NULL, SEND_CFG);
    m_client->write (msg);
}

void RPiServer::slotRecvConfig ()
{
    //
    // TODO
    // What do we want to do when we receive the config file?
    // Display it?
    //
    QString cfg = m_dataPro->getData ().data ();
    ui->responseBrowser->clear();
    ui->responseBrowser->append(cfg);
}

void RPiServer::on_sendButton_clicked()
{
    slotSendCommand (ui->cmdEdit->text().toInt());
}
