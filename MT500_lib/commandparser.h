#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <QObject>
#include "commands.h"

class CommandParser : public QObject
{
    Q_OBJECT
public:
    CommandParser();

    void parseCommand (unsigned char command);

signals:

    void sigSendImage ();
    void sigRecvImage ();
    void sigSendTime ();
    void sigRecvTime ();

public slots:

};

#endif // COMMANDPARSER_H
