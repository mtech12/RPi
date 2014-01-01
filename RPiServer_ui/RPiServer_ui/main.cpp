#include "rpiserver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RPiServer w;
    w.show();

    return a.exec();
}
