#include <QCoreApplication>
#include "downloader.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Downloader d;
    d.doDownload();

    return a.exec();
}
