#include <QCoreApplication>
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QTimer>
#include <QSslConfiguration>
#include <QString>
#include <QByteArray>

class HttpTest:public QObject{
Q_OBJECT
public:
    void testGet(); //发送http请求
public slots:
    void replyFinish(QNetworkReply*); //用于处理响应返回的数据
};


void HttpTest::testGet(){
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkRequest request;

    request.setUrl(QUrl("http://baidu.com"));
    QNetworkReply* reply = manager->get(request);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinish(QNetworkReply*)));
}


void HttpTest::replyFinish(QNetworkReply* reply)
{
    qDebug()<<reply->readAll();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    HttpTest cTest;
    cTest.testGet();

    return a.exec();
}
