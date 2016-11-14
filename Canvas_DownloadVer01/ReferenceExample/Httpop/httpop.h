#ifndef HTTPOP_H
#define HTTPOP_H

#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QNetworkReply>
#include <QByteArray>
#include <QUrl>
#include <QDebug>
#include <QObject>

#define POST "POST"
#define GET "GET"

// Http Operation Class
class HttpOp
{
private:
    QNetworkRequest mNetRequest;
    QNetworkAccessManager *mNetManager;
    QByteArray mQdataArray;
    QString mmode;
    QString mUrl;
    QString mdata;
    void init();
public:
    HttpOp();
    ~HttpOp();
    QNetworkAccessManager* send(QNetworkReply* &reply);
    HttpOp* data(QString sdata);
    HttpOp* mode(QString smode);
    HttpOp* url(QString surl);
protected slots:
    void testfinish(QNetworkReply *reply);
};

#endif // HTTPOP_H
