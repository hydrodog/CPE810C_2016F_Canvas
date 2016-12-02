#include "httpop.h"




int main(int argc, char *argv[])
{
    HttpOp A;
    QByteArray byte_array;
    A.HttpOp();
    QNetworkReply *reply;
    QNetworkAccessManager* QNetworkManager;
    QNetworkManager = HttpOp()->url("google.com");
    QObject::connect(QNetworkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(LoginFinish(QNetworkReply*)));

//    server = new QTcpServer(this);
//    server = new QTcpServer(this);

//    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
}
