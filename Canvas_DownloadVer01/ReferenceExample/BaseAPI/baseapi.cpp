#include "baseapi.h"

BaseAPI::BaseAPI()
{
    httpRequest.setRawHeader("Accept", API_ACCEPT);
    httpRequest.setRawHeader("User-Agent", API_USER_AGENT);
    httpRequest.setRawHeader("X-XXX-API-Key", API_KEY);
    httpRequest.setRawHeader("X-XXX-API-Secret", API_SECRET);
    httpRequest.setRawHeader("Accept-Encoding", "gzip, deflate");
    httpRequest.setRawHeader("Content-Type", "application/json");

    settings = new QSettings("XXX");
    QString id = settings->value(SETTING_ACCOUNT_ID, "").toString();
    QString token = settings->value(SETTING_ACCOUNT_TOKEN, "").toString();

    if(!id.isEmpty()) {
        httpRequest.setRawHeader("X-XXX-User-ID", id.toStdString().c_str());
    }

    if (!token.isEmpty()) {
        httpRequest.setRawHeader("X-XXX-User-Token", token.toStdString().c_str());
    }

    qDebug() << "BaseAPI...id:" << id << " token:" + token;

    QObject::connect(&networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(serviceRequestFinished(QNetworkReply*)));
}

BaseAPI::~BaseAPI()
{
    networkAccessManager.disconnect();
    if (settings){
        delete settings;
        settings = nullptr;
    }
}

void BaseAPI::get(const QString url)
{
    httpRequest.setUrl(QUrl(url));
    networkAccessManager.get(httpRequest);
}

void BaseAPI::post(const QString url, const QByteArray &data)
{
    httpRequest.setUrl(QUrl(url));
    networkAccessManager.post(httpRequest, data);
}

void BaseAPI::serviceRequestFinished(QNetworkReply *reply)
{
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    qDebug() << "BaseAPI...serviceRequestFinished...statusCode:" << statusCode;

    if(reply->error() == QNetworkReply::NoError) {
        requestFinished(reply, reply->readAll(), statusCode);
    } else {
        requestFinished(reply, "", statusCode);
    }

    // At the end of that slot, we won't need it anymore
    reply->deleteLater();
}
