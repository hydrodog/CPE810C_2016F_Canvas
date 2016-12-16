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
#include <map>

extern vector<QString> student;// store student api
extern vector<QString> filenames;// json file of every student
extern vector<QString> userid;// temporary store student id
extern vector<double> assignmentid;// temporary store assignment id
extern vector<double> assignmentscore;// temporary store assignment score
extern map<double, vector<double> > everyAss;// hmap to store score of every assignment( for other team)
extern vector<QString> fileApi;// store assignment api
extern vector<QString> fileAddress;// json file of assignment api
extern vector<QString> submissionName;// store submission name
extern vector<QString> downloadAdd;// store download Url
extern vector<double> AssId;// store assignment id


canvasConnection::canvasConnection(QObject *parent) :
    QObject(parent)
{
    m_pNetworkManager = new QNetworkAccessManager(this);
    m_pNetworkReply = NULL;
}

//show data
void canvasConnection::showdata() {
    for (int i = 0; i < userid.size() ; i++)      //vector userid, assignmentid,assignmentscore have the same size;
    qDebug().noquote() << "userid : " <<userid[i] << " assignment_id: " << assignmentid[i] <<" score: " << assignmentscore[i] << '\t';
}

//store score of every assignment in a hashmap
void canvasConnection::everyAssScore(){
    for(int j = 0; j < 10; ++j){
        vector<double> ve;
        AssId.push_back(assignmentid[j]);
        for(int i = j; i < 70; i += 10){
            ve.push_back(assignmentscore[i]);
        }
        double ass = assignmentid[j];
        everyAss.insert(make_pair(ass, ve));
        ve.clear();
    }
}

