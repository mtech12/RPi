#include <QCoreApplication>
#include "rpiclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    RPiClient r;

    return a.exec();
}
