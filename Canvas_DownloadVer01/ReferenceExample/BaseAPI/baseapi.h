#ifndef BASEAPI_H
#define BASEAPI_H

#include <QSettings>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>


class BaseAPI : public QObject
{
    Q_OBJECT

public:
    BaseAPI();
    ~BaseAPI();
    void get(const QString url);
    void post(const QString url, const QByteArray &data);

protected:
    virtual void requestFinished(QNetworkReply *reply, const QByteArray data, const int statusCode) = 0;

public slots:
    void serviceRequestFinished(QNetworkReply *reply);

private:
    QNetworkRequest httpRequest;
    QNetworkAccessManager networkAccessManager;
    QSettings *settings;
};

#endif // BASEAPI_H
