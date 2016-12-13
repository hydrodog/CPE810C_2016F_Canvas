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
    //explicit Downloader(QObject *parent = 0);
    explicit canvasConnection(QObject *parent = 0);
    //send network requests with url.
    void sendRequest(const QString &strUrl);
    void sendAssRequest(const QString &strUrl);
    //Read JSON
    void readJson();
    void setFilename(QString fN);
    void doDownload();
    void extract();
    void showdata();
    void everyAssScore();
    void readAttachment();
    void downAssignment();
    void doDownload(const QUrl &a);
    void sendpostrequest(const QUrl &url, const QByteArray &data);
signals:
    //declare signal when network requests end
    void signal_requestFinished(bool bSuccess,const QString& strResult);
public slots:
    //network requests end
    //void quit();
     void replyFinished (QNetworkReply *reply);
};
#endif CANVASCONNECTION_H
