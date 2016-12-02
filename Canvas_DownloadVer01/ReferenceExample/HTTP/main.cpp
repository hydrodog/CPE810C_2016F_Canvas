#include <QCoreApplication>

#include "downloadmanager.h"
#include <QTimer>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    DownloadManager manager;

    // This static single-shot timer fires instantly, only once,
    // while non-single-shot timers fire every interval milliseconds.
    QTimer::singleShot(0, &manager, SLOT(execute()));
    // manager.execute(); (This would be the same)

    app.exec();
}
