#ifndef RPISERVER_H
#define RPISERVER_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QDir>
#include <QStringList>
#include <QFileSystemWatcher>
#include <QTimer>

#include "tcpserver.h"
#include "imageprocessor.h"
#include "tcpclient.h"
#include "dataprotocol.h"
#include "commandparser.h"
#include "utilities.h"
#include "commands.h"

#define SLIDESHOW_INTERVAL_MSEC 2500

namespace Ui {
class RPiServer;
}

class RPiServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit RPiServer(QWidget *parent = 0);
    ~RPiServer();

signals:

public slots:

    void slotGotData(QByteArray data);
    void slotSendCommand (unsigned char command);
    void slotRecvImage ();
    void slotSendTime ();
    void slotRequestResend ();
    void slotResend ();
    void slotRequestConfig ();
    void slotRecvConfig ();
    void slotSetImage (const QString& image);
    void slotUpdateImageList (QString fileChanged);
    void slotSlideshow ();

private slots:
    void on_sendButton_clicked();
    void on_prevButton_clicked();
    void on_nextButton_clicked();
    void on_takePicture_clicked();
    void on_getConfig_clicked();
    void on_slideshowButton_clicked();

private:

    Ui::RPiServer *ui;
    QVariantMap m_cfg;
    TCPServer *m_server;
    ImageProcessor *m_ip;
    TCPClient *m_client;
    DataProtocol *m_dataPro;
    CommandParser *m_cp;
    QStringList m_imageList;
    QFileSystemWatcher *m_imageWatcher;
    int m_imageIndex;
    bool m_slideshowRunning;
    QTimer *m_slideshowTimer;
};

#endif // RPISERVER_H
