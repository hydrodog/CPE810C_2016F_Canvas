  #include <QtNetwork>
  #include <QCoreApplication>
  #include <QDebug>
  void sendRequest();

  int main(int argc, char *argv[])
  {
      QCoreApplication a(argc, argv);
      sendRequest();
      return a.exec();
  }

  void sendRequest(){
      QEventLoop eventLoop;

      // "quit()" the event-loop, when the network request "finished()"
      QNetworkAccessManager mgr;
      QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
      QByteArray postdata;
      postdata.append("{\"comment\":{\"text_comment\" : \"111111111111111\"},\"submission\":{\"posted_grade\": \"10\"} }");

      // the HTTP request
      QNetworkRequest req( QUrl( QString("https://sit.instructure.com/api/v1/courses/133/assignments/46024/submissions/19850") ) );
      req.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
      req.setRawHeader("Authorization","Bearer 1030~4MvxMX4ZFH8LCUAe9pFKhNUwFc6o4PnsFny5vlO4sLdyExxx3B9SR3ULM2nzl211");
      QNetworkReply *reply = mgr.put(req,postdata);
      eventLoop.exec(); // blocks stack until "finished()" has been called

      if (reply->error() == QNetworkReply::NoError) {
          //success
          qDebug() << "Success"<<reply->readAll();
          delete reply;
      }
      else {
          //failure
          qDebug() << "Failure"<<reply->errorString() ;
          delete reply;
      }

  }
