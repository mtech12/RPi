#ifndef SERIAL_H
#define DATAPROTOCOL_H

#include <QByteArray>
#include <QBuffer>
#include <QDateTime>
#include <QDebug>

/*
 *
 * Very simple implementation of the HDLC data protocol.
 * http://en.wikipedia.org/wiki/High-Level_Data_Link_Control
 *
 * Frame:
 *    [frame 8-bits][command 8-bits][control 8-bits][data 0-n bits][CRC 16-bits][frame 8-bits]
 *
 * Note - we are using the address field to send commands
 */


class DataProtocol
{
public:
    DataProtocol();

    /*
     * Returns a QByteArray with computed CRC16
     * and correct framing sequence
     */
    QByteArray encode(QByteArray dataToSend, unsigned char command);

    /*
     * Returns data from received frame if CRC16
     * matches else returns a null QByteArray
     */
    unsigned char decode(QByteArray recvFrame);

    QByteArray getData ();

private:

    unsigned char m_frame, m_command, m_control;
    QByteArray m_data;
};

#endif // DATAPROTOCOL_H
