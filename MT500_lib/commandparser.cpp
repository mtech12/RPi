#include "commandparser.h"

CommandParser::CommandParser() : QObject ()
{
}

void CommandParser::parseCommand (unsigned char command) {

    switch (command) {
    case SEND_IMAGE:
        emit sigSendImage();
        break;
    case IMAGE_RESPONSE:
        emit sigRecvImage();
        break;
    case SYNC_TIME:
        emit sigSendTime ();
        break;
    case TIME_RESPONSE:
        emit sigRecvTime ();
        break;
    case RESEND:
        emit sigResend ();
        break;
    case REBOOT:
        emit sigReboot ();
        break;
    case SEND_CFG:
        emit sigSendCfg ();
        break;
    case CFG_RESPONSE:
        emit sigRecvCfg ();
        break;
    case NEW_CFG:
        emit sigNewCfg ();
        break;
    case CRC_MISMATCH:
        emit sigCRCMismatch ();
        break;
    default:
        break;
    }
}
