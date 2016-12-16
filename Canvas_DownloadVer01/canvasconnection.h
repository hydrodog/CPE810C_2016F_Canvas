#ifndef CANVASCONNECTION_H
#define CANVASCONNECTION_H
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QSslConfiguration>
#include <QString>
#include <QByteArray>
#include <iostream>

using namespace std;

class canvasConnection : public QObject
{
    Q_OBJECT
private:
    //The QNetworkAccessManager class allows the application to send network requests and receive replies.
    QNetworkAccessManager* m_pNetworkManager;
    //The QNetworkReply class contains the data and headers for a request sent with QNetworkAccessManager.
    QNetworkReply* m_pNetworkReply;
    //Current url
    QString m_strUrl;
    QString fileName;
    QNetworkAccessManager *manager;
public:
    explicit canvasConnection(QObject *parent = 0);
    //send network requests with url.
    void sendRequest(const QString &strUrl);
    void sendAssRequest(const QString &strUrl);
    //Read JSON
    void readJson();
    //download students' json files
    void doDownload();
    //download json file of assignments
    void downAssignment();
    //extract data ( userif, assignmentId, assignmentScore)
    void extract();
    //show data
    void showdata();
    //store score of every assignment in a hashmap
    void everyAssScore();
    //read attachment in json file
    void readAttachment();
    // download submissions of students
    void doDownload(const QUrl &a);
signals:
    //declare signal when network requests end
    void signal_requestFinished(bool bSuccess,const QString& strResult);
public slots:
    //network requests end
     void replyFinished (QNetworkReply *reply);
};
#endif CANVASCONNECTION_H
