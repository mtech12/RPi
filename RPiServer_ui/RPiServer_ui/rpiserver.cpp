#include "rpiserver.h"
#include "ui_rpiserver.h"
#include <QPixmap>


RPiServer::RPiServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RPiServer)
{
    ui->setupUi(this);

    m_imageIndex = -1;
    m_slideshowRunning = false;
    m_cfg = Utilities::getConfig ("config.mts");

    m_server = new TCPServer ();
    m_ip = new ImageProcessor ();
    m_dataPro = new DataProtocol ();
    m_client = new TCPClient (m_cfg[CLIENT_IP].toString ());
    m_cp = new CommandParser ();
    m_imageWatcher = new QFileSystemWatcher();
    m_slideshowTimer = new QTimer ();

    connect(m_server, SIGNAL(sigGotData(QByteArray)), this, SLOT(slotGotData(QByteArray)));

    m_imageWatcher->addPath(m_cfg[IMAGE_DIRECTORY].toString());
    connect(m_imageWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(slotUpdateImageList(QString)));

    connect(m_slideshowTimer, SIGNAL(timeout()), this, SLOT(slotSlideshow()));

    //
    // Slots to respond to Command Parser signals
    //
    connect(m_cp, SIGNAL(sigRecvImage()), this, SLOT(slotRecvImage ()));
    connect(m_cp, SIGNAL(sigSendTime()), this, SLOT(slotSendTime ()));
    connect(m_cp, SIGNAL(sigCRCMismatch()), this, SLOT(slotRequestResend ()));
    connect(m_cp, SIGNAL(sigResend()), this, SLOT(slotResend ()));
    connect(m_cp, SIGNAL(sigRecvCfg()), this, SLOT(slotRecvConfig ()));

    slotUpdateImageList ("constructor");
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
    if(ui->cmdEdit->text() != "") slotSendCommand (ui->cmdEdit->text().toInt());
}

void RPiServer::slotSetImage(const QString &image)
{
    qDebug() << QString("Setting image to %1").arg(image);
    ui->imageTitle->setText(image);
    QPixmap mypix (QString("%1%2").arg(m_cfg[IMAGE_DIRECTORY].toString()).arg(image));
    mypix = mypix.scaled (250, 250);
    ui->imageLbl->setPixmap(mypix);
}

void RPiServer::slotUpdateImageList(QString fileChanged)
{
    qDebug() << QString("File %1 changed.").arg(fileChanged);
    QStringList filters;
    filters << "*.jpg";
    QDir imageDir = QDir(m_cfg[IMAGE_DIRECTORY].toString ());
    m_imageList = imageDir.entryList(filters, QDir::Files, QDir::Time);
    if (m_imageList.size() > 0 && m_imageIndex == -1) {
        m_imageIndex = 0;
        slotSetImage(m_imageList.at(0));
    }
    qDebug() << QString("Size of image list: %1").arg(m_imageList.size());
}

void RPiServer::on_prevButton_clicked()
{
    if(m_imageList.size() > 0) {
        m_imageIndex--;
        if (m_imageIndex < 0) m_imageIndex = 0;
        slotSetImage(m_imageList.at(m_imageIndex));
    }
}

void RPiServer::on_nextButton_clicked()
{
    if(m_imageList.size() > 0) {
        m_imageIndex++;
        if (m_imageIndex >= m_imageList.size()) m_imageIndex = m_imageList.size() - 1;
        slotSetImage(m_imageList.at(m_imageIndex));
    }
}

void RPiServer::on_takePicture_clicked()
{
    slotSendCommand (0);
}

void RPiServer::on_getConfig_clicked()
{
    slotSendCommand (6);
}

void RPiServer::on_slideshowButton_clicked()
{
    if(m_imageList.size() > 0) {
        m_slideshowRunning = !m_slideshowRunning;
        if(m_slideshowRunning == true) {
            ui->slideshowButton->setText("Stop");
            m_imageIndex = 0;
            slotSetImage(m_imageList.at(0));
            m_slideshowTimer->start(SLIDESHOW_INTERVAL_MSEC);
        }
        else {
            ui->slideshowButton->setText("Slideshow");
            m_slideshowTimer->stop();
        }
    }
}

void RPiServer::slotSlideshow()
{
    m_imageIndex++;
    if (m_imageIndex == m_imageList.size()) {
        m_imageIndex = m_imageList.size() - 1;
        m_slideshowTimer->stop();
        m_slideshowRunning = !m_slideshowRunning;
        ui->slideshowButton->setText("Slideshow");
    }
    else slotSetImage(m_imageList.at(m_imageIndex));
}
