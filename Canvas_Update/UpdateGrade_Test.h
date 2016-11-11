#ifndef UpdateGrade_Test_H
#define UpdateGrade_Test_H
#include <QCoreApplication>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <Qssl>
#include <QFile>

/*  This is to test the connection with URL by Qurl because it hard to connect by cURL at present. */

class UpdateGrade_Test{
private:
  QNetworkAccessManager *_uploadManager;
  QNetworkReply *_reply;
  char* m_buf;
private slots:
  void replyFinished( QNetworkReply* );
  void upLoadError(QNetworkReply::NetworkError errorCode);
  void OnUploadProgress( qint64 bytesSent, qint64 bytesTotal);
};

#endif // UpdateGrade_Test_H
