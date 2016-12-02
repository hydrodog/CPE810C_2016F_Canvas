#include "canvasconnection.h"
#include <QTextCodec>
#include <QtNetwork>
#include <QByteArray>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QCoreApplication>
#include <QJsonValue>
#include <QJsonArray>
#include <vector>

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
    QFile file(fileName);
	//Send request to Canvas by using token.
    QNetworkRequest netRequest;
    //Set the information of url.
    netRequest.setUrl(QUrl(strUrl));
    netRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    netRequest.setRawHeader("Accept", "application/json");
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

//set name of file
void canvasConnection::setFilename(QString fN){
    fileName = fN;
}

//read Json
void canvasConnection::readJson(){
    vector<double> vec;
    QString settings;
    QFile file;
    file.setFileName(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    settings = file.readAll();
    file.close();
    //qWarning() << settings;
    QJsonDocument sd = QJsonDocument::fromJson(settings.toUtf8());
    qWarning() << sd.isNull(); // <- print false :)
    qWarning() << sd.isArray();
    qWarning() << sd.isObject();
    //Json Array
    QJsonArray sett3 = sd.array();
    qWarning() << sett3;

    qWarning() << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

    for(int i = 0; i < 10; i++){
        //convert from QJsonValue to QJsonObject
        double AAA = sett3.at(i).toObject().take(QString("assignment_id")).toDouble();
        std::cout.precision(0);
        //print assignment id.
        std::cout << "assignment_id : " << std::fixed << (AAA - 1.03*pow(10,16)) << endl;
        std::cout << "score : ";
        //print score.
        qDebug() << sett3.at(i).toObject().take(QString("submission")).toObject().take(QString("score")).toDouble();
        vec.push_back(sett3.at(i).toObject().take(QString("submission")).toObject().take(QString("score")).toDouble());
    }
    for(int i = 0; i<10; i++)
        std::cout << vec[i] << "+";
    std::cout << endl;
}
