#include "httpfun.h"
#include <QCoreApplication>
using namespace std;

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);
    HttpFun A;
    HttpFun B;
    // A.sendRequest("http://www.cnblogs.com/Travis990/p/4483538.html");
    B.sendRequest("http://baidu.com");
    return a.exec();
}

