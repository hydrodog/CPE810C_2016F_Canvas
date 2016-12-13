#include "downloader.h"

Downloader::Downloader(QObject *parent) :
    QObject(parent)
{
}

void Downloader::doDownload(const QUrl &a)
{
    manager = new QNetworkAccessManager(this);
    //QUrl a("https://canvas.instructure.com/api/v1/courses/10300000000000133/assignments/10300000000046025?access_token=1030~y2v695pyuP5tf7SbJVuosakVODI0LyqrA5MXFWgJYscYmgOSL3VqXezUdOSyMYxL");
    //connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(a));


}
void Downloader::sendpostrequest(const QUrl &url, const QByteArray &data)
{
           manager = new QNetworkAccessManager(this);
           const QUrl mUrl = url;
           const QByteArray login = data;
           QNetworkRequest r(mUrl);
           connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
           manager->post(r, data);

}

void Downloader::replyFinished (QNetworkReply *reply)
{
    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
    }
    else
    {
        qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
        qDebug() << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();
        qDebug() << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
        qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
        qDebug() << "SUCCESS!";

        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if(statusCode == 302)
        {
            QUrl newUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
            QNetworkRequest newRequest(newUrl);
            qDebug() << " redirected" ;
            manager->get(newRequest);
            return;
        }




        QFile *file = new QFile("test.zip");
        if(file->open(QFile::Append))
        {
           file->write(reply->readAll());
           file->flush();
           file->close();
        }
        delete file;
    }

    reply->deleteLater();
}
