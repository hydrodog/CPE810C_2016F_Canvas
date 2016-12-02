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
#include <vector>
extern vector<QString> student;
extern vector<QString> filenames;
extern vector<QString> userid;
extern vector<QString> assignmentid;
extern vector<QString> assignmentscore;

canvasConnection::canvasConnection(QObject *parent) :
    QObject(parent)
{
    m_pNetworkManager = new QNetworkAccessManager(this);
    m_pNetworkReply = NULL;
}

//Send network requests
void canvasConnection::sendRequest(const QString &strUrl)
{   static int a = 0;
	m_strUrl = strUrl;
	//Create custom temporary event loop on stack
    QEventLoop eventLoop;
	//Open a file
    QFile file(filenames[a]);
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
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
           return;
        file.write(m_pNetworkReply->readAll());
        file.flush();
        file.close();
        qDebug() << "Success";
        a++;
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
    //vector<double> vec;
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
         long double AAA = sett3.at(i).toObject().take(QString("assignment_id")).toDouble();
        std::cout.precision(0);
        //print assignment id.
        std::cout << "assignment_id : " << std::fixed << (AAA - 1.03*pow(10,16)) << endl;
        std::cout << "score : ";
        //print score.
        qDebug() << sett3.at(i).toObject().take(QString("submission")).toObject().take(QString("score")).toDouble();

    }
}


void canvasConnection::doDownload(){
    QString content;
    QFile file ;
    for (vector<QString>::iterator m = student.begin(); m != student.end(); ++m)
             sendRequest(*m);

}

void canvasConnection::extract(){
    QString content;
    QFile file;
    for(vector<QString>::iterator m = filenames.begin();m!=filenames.end();++m ) {
    file.setFileName(*m);

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    content = file.readAll();
    file.close();

    QJsonDocument sd = QJsonDocument::fromJson(content.toUtf8());
    qWarning() << "the last 5 digit of user ID" << *m;
    qWarning() <<"sd.isNull() :" << sd.isNull(); // <- should print false to prove it is not empty.
    qWarning() <<"sd.isArray() :"<< sd.isArray();
    qWarning() << "sd.isObject()"<< sd.isObject();
    QJsonArray sett3 = sd.array();

    for(int i = 0; i < 10; i++){

    double assignment_id = sett3.at(i).toObject().take(QString("assignment_id")).toDouble();
    QString assign_id = QString("%1").arg(assignment_id, 0, 'f', 0); //set the precison.

        qDebug().noquote() <<"assignment_id :"<< assign_id ;


    double Score = sett3.at(i).toObject().take(QString("submission")).toObject().take(QString("score")).toDouble();
    QString score = QString("%1").arg(Score, 0, 'f', 0)  ;
        qDebug() <<"score :"<< score;

        userid.push_back(*m);
        assignmentid.push_back(assign_id);
        assignmentscore.push_back(score);


 }
          qDebug() << "\n";

   }
}


void canvasConnection::showdata() {
    for (int i = 0; i < userid.size() ; i++)      //vector userid, assignmentid,assignmentscore have the same size;
   qDebug().noquote() << "userid : " <<userid[i] << " assignment_id: " << assignmentid[i] <<" score: " << assignmentscore[i] << '\t';

}






