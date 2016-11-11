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

void sendRequest(const QString strUrl);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //send request to Canvas by using token.
    sendRequest("https://canvas.instructure.com/api/v1/courses?access_token=1030~y2v695pyuP5tf7SbJVuosakVODI0LyqrA5MXFWgJYscYmgOSL3VqXezUdOSyMYxL");
    return a.exec();

}

void sendRequest(const QString strUrl){

    const QString m_strUrl = strUrl;
    //create a download file
    QFile file("out.json");
    // create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager Canvas;
    QObject::connect(&Canvas, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // send request to Canvas by using token
    QNetworkRequest request;
    request.setUrl(QUrl(strUrl));

   //test of using another api.
   //QNetworkRequest request( QUrl( QString("https://canvas.instructure.com/api/v1/courses/14812/assignments/55596?access_token=1030~y2v695pyuP5tf7SbJVuosakVODI0LyqrA5MXFWgJYscYmgOSL3VqXezUdOSyMYxL") ) );
    QNetworkReply *reply = Canvas.get(request);

    eventLoop.exec(); // blocks stack until "finished()" has been called

    QTextStream out(&file);
    if (reply->error() == QNetworkReply::NoError) {

        //  success
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        file.write(reply->readAll());
        qDebug() << "Success" <<reply->readAll();
        delete reply;

    }
    else {
        //  failure
        qDebug() << "Failure" ;
        delete reply;
    }
}
