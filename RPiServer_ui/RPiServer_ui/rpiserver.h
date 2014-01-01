#ifndef RPISERVER_H
#define RPISERVER_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>

#include "tcpserver.h"
#include "imageprocessor.h"
#include "tcpclient.h"
#include "dataprotocol.h"
#include "commandparser.h"
#include "utilities.h"
#include "commands.h"

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

private slots:
    void on_sendButton_clicked();

private:

    Ui::RPiServer *ui;
    QVariantMap m_cfg;
    TCPServer *m_server;
    ImageProcessor *m_ip;
    TCPClient *m_client;
    DataProtocol *m_dataPro;
    CommandParser *m_cp;
};

#endif // RPISERVER_H
