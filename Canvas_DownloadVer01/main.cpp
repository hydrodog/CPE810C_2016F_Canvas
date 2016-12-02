#include "canvasconnection.h"
#include <QCoreApplication>
#include <QFileInfo>
using namespace std;

//void httpReadyRead();
//void httpFinished();


//TODO:download JSON file then put data into datd-base.
int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);
    canvasConnection A;
    canvasConnection B;
    canvasConnection C;
    A.sendRequest("https://canvas.instructure.com/api/v1/courses/10300000000000133/analytics/users/10300000000020168/assignments?access_token=1030~ITJlnLeBaoqbzneuPAfdNLG5e9jAZqVHMiZWxF3FbvTG31U6l5adkBJcqOf8lCIO");
  // B.sendRequest("http://pic1.win4000.com/wallpaper/3/51e8a7e0581f6.jpg");
  //  C.sendRequest("https://canvas.instructure.com/api/v1/courses/10300000000000133/assignments/10300000000046025?access_token=1030~ITJlnLeBaoqbzneuPAfdNLG5e9jAZqVHMiZWxF3FbvTG31U6l5adkBJcqOf8lCIO");
//    MyDownloader m_downLoder;
//    m_downLoder.setData(QUrl("https://canvas.instructure.com/courses/1030~133/assignments/1030~46025/submissions?zip=1"),QString("C:\\Users\\Freelancer\\Desktop\\result"));
//    m_downLoder.cancel();
//    m_downLoder.getFile();
//    QUrl url = QUrl("https://canvas.instructure.com/courses/1030~133/assignments/1030~46025/submissions?zip=1");
//    QFileInfo info(url.path());
//    QString fileName(info.fileName());
//    QFile *file = new QFile("fileName");
//    QNetworkAccessManager *manager;
//    QNetworkReply* reply = manager->get(QNetworkRequest(url));
//    connect(reply, SIGNAL(finished()),this, SLOT(httpFinished()));
//    connect(reply, SIGNAL(readyRead()),this, SLOT(httpReadyRead()));
//   // connect(reply, SIGNAL(downloadProgress(qint64,qint64)),this, SLOT(updataReadProcess(qint64,qint64)));
    QString t = "submissions9.txt";
    A.readJson(t);
    return a.exec();
}


