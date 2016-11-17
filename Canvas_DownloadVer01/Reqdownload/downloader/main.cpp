#include <QCoreApplication>
#include "downloader.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    const QUrl b("https://www.google.com");
    QByteArray data;
    data.append("username=mhe6&password=Stevens586341");
    Downloader d;
    d.sendpostrequest(b,data);
    d.doDownload(b);


    return a.exec();
}
