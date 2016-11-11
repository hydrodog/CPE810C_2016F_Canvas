#include <QCoreApplication>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <Qssl>
#include <QTextStream>
#include <QFile>
using namespace std;

void sendRequest();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    sendRequest();
    return a.exec();

}

void sendRequest(){

    QFile file("out.json");
    // create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
      QNetworkRequest req( QUrl( QString("https://canvas.instructure.com/api/v1/courses?access_token=1030~HmnfpMmIn7wYqD48N0upMQfEbVMYsCPUIUcVnCnZyQrluVPp6l40GaHb3jsXvX3u") ) );
   // QNetworkRequest req( QUrl( QString("https://canvas.instructure.com/api/v1/courses/14812/assignments/55596?access_token=1030~HmnfpMmIn7wYqD48N0upMQfEbVMYsCPUIUcVnCnZyQrluVPp6l40GaHb3jsXvX3u") ) );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    QTextStream out(&file);
    if (reply->error() == QNetworkReply::NoError) {

        //success
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        file.write(reply->readAll());
        qDebug() << "Success" <<reply->readAll();
        delete reply;

    }
    else {
        //failure
        qDebug() << "Failure" ;
        delete reply;
    }
}


