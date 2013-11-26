#include "dataprotocol.h"

DataProtocol::DataProtocol()
{
    m_frame = 0x7E; /* Framing byte */
    m_command = 0xFF; /* Default command - not used */
    m_control = 0x7D; /* Control byte also escape byte */
    m_data = NULL;
}

QByteArray DataProtocol::encode(QByteArray dataToSend, unsigned char command)
{
    m_command = command;

    /*
     * Loop over dataToSend byte by byte and check for the occurence
     * of the framing byte or the escape byte. If either is found
     * we insert an escape byte in front of it and invert bit 5
     * of the original octect.
     */
    for(int i = 0; i < dataToSend.size(); i++) {
        if(dataToSend.at(i) == m_frame || dataToSend.at(i) == m_control) {
            dataToSend[i] = dataToSend[i] ^ 0x20;
            dataToSend.insert(i, m_control);
        }
    }

    /*
     * 16-bit CRC is computed over the address,
     * control, and dataToSend
     */
    QByteArray toCRC;
    toCRC.append(m_command);
    toCRC.append(m_control);
    toCRC.append(dataToSend);
    /*
     * Compute CRC
     *
     */
    quint16 crc1 = qChecksum(toCRC.data(), toCRC.length());
    qDebug() << QString("CRC Transmit: %1").arg(crc1, 0, 16);
    unsigned char high = crc1 >> 8;
    unsigned char low =  crc1 & 0x00FF;

    /*
     * Complete frame to send.
     */
    QByteArray toSend;
    toSend.append(m_frame); /* Framing byte */
    toSend.append(m_command); /* Random address */
    toSend.append(m_control); /* Control (escape) byte */
    toSend.append(dataToSend); /* data to send */
    toSend.append(high); /* High byte of 16-bit CRC */
    toSend.append(low); /* Low byte of 16-bit CRC */
    toSend.append(m_frame); /* Framing byte */

    return toSend;
}

unsigned char DataProtocol::decode(QByteArray recvFrame)
{
    /*
     * Extract command
     */
    unsigned char command = recvFrame.at(1);

    int sizeOfRecv = recvFrame.size();
    /*
     * Extract received CRC
     */
    unsigned char high = recvFrame.at(sizeOfRecv - 3);
    unsigned char low = recvFrame.at(sizeOfRecv - 2);
    quint16 crc = high << 8 | low;
    qDebug() << QString("CRC Received: %1").arg(crc, 0, 16);
    QByteArray dataRecv;
    /*
     * Extract data from recieved frame
     *
     */
    for(int i = 3; i < sizeOfRecv - 3; i++) {
        dataRecv.append(recvFrame.at(i));
    }
    /*
     * Compute CRC
     */
    QByteArray toCRC;
    toCRC.append(command);
    toCRC.append(m_control);
    toCRC.append(dataRecv);
    quint16 crc1 = qChecksum(toCRC.data(), toCRC.length());
    qDebug() << QString("Checksum Calculated: %1").arg(crc1, 0, 16);
    /*
     * If the received CRC = the calculated CRC then
     * return the data else return NULL
     */
    if(crc == crc1) {
        /*
         * Undo escaping of data
         *
         */
        qDebug() << "Checksums match!";
        for(int i = 0; i < dataRecv.size(); i++) {
            if(dataRecv.at(i) == m_control) {
                dataRecv[i+1] = dataRecv[i+1] ^ 0x20;
                dataRecv.remove(i,1);
            }
        }
        m_data = dataRecv;
        return command;
    }
    else return 0xFF;
}

QByteArray DataProtocol::getData ()
{
    return m_data;
}
