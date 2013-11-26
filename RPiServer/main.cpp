#include <QCoreApplication>

#include "rpiserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    RPiServer r;

    return a.exec();
}
