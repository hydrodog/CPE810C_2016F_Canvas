#include "canvasconnection.h"
#include <QTextCodec>
#include <iostream>
#include <QtNetwork>
#include <QByteArray>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QCoreApplication>
#include <iostream>
#include <QJsonValue>
#include <QJsonArray>


canvasConnection::canvasConnection(QObject *parent) :
    QObject(parent)
{
    m_pNetworkManager = new QNetworkAccessManager(this);
    m_pNetworkReply = NULL;
}

//Send network requests
void canvasConnection::sendRequest(const QString &strUrl)
{
	m_strUrl = strUrl;
	//Create custom temporary event loop on stack
    QEventLoop eventLoop;
	//Open a file
    QFile file("submissions9.txt");
	//Send request to Canvas by using token.
    QNetworkRequest netRequest;
    //Set the information of url.
    netRequest.setUrl(QUrl(strUrl));


    netRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    netRequest.setRawHeader("Accept", "application/json");


//    QString authString = (QString)"shu14 " + ":" + (QString)" Free921227";
//    QString base64String = "Bearer " + authString.toUtf8().toBase64();
    //QString at = "Bearer " + (QString)"1030~ITJlnLeBaoqbzneuPAfdNLG5e9jAZqVHMiZWxF3FbvTG31U6l5adkBJcqOf8lCIO";
    //netRequest.setRawHeader("Authorization","Bearer 1030~y2v695pyuP5tf7SbJVuosakVODI0LyqrA5MXFWgJYscYmgOSL3VqXezUdOSyMYxL");
    //netRequest.setRawHeader("Authorization", base64String.toUtf8());


    /*Posts a request to obtain the contents of the target request and
    returns a new QNetworkReply object opened for reading*/
    m_pNetworkReply =m_pNetworkManager->get(netRequest);
    //Signal when the network requests end
    QObject::connect(m_pNetworkManager,SIGNAL(finished(QNetworkReply*)),&eventLoop,SLOT(quit()));
	// blocks stack until "finished()" has been called
	eventLoop.exec();
    if (m_pNetworkReply->error() == QNetworkReply::NoError) {
        //success
        if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
           return;
        file.write(m_pNetworkReply->readAll());
        file.flush();
        file.close();
        qDebug() << "Success";
		//release memory
        delete m_pNetworkReply;
    }
    else {
        //failure
        qDebug() << "Failure" ;
		//release memory
        delete m_pNetworkReply;
    }
}

void canvasConnection::readJson(QString A){

    QString settings;
    QFile file;
    file.setFileName(A);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    settings = file.readAll();
    file.close();
    //qWarning() << settings;
    QJsonDocument sd = QJsonDocument::fromJson(settings.toUtf8());
    qWarning() << sd.isNull(); // <- print false :)
    qWarning() << sd.isArray();
    qWarning() << sd.isObject();
    //封装JSON对象
    QJsonArray sett3 = sd.array();
   // QJsonObject sett2 = sd.object();
    qWarning() << sett3;
    QJsonArray::iterator it;
    //qWarning() << sett2;
    qWarning() << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

    qWarning() << sett3[1];

    qWarning() << sett3[1].isObject();

//   QJsonObject SET = sett3[1];

//   qWarning() << SET["assignment_id"].toInt();


    for (it = sett3.begin(); it != sett3.end(); ++it){
        qDebug() << *it;
        //QString a = *it;
        qWarning() << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
        qWarning() << (*it["assignment_id"]).toInt();


    }
    //qWarning() << sett2[QString("title")].toString();  // <- print my title
}
