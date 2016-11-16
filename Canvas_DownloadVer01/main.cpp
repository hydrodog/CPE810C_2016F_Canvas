#include "canvasconnection.h"
#include <QCoreApplication>
using namespace std;
//TODO:download JSON file then put data into datd-base.
int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);
    canvasConnection A;
    canvasConnection B;
    canvasConnection C;
    A.sendRequest("http://www.36wu.com");
   //B.sendRequest("http://baidu.com");
   // C.sendRequest("https://canvas.instructure.com/api/v1/courses?access_token=1030~y2v695pyuP5tf7SbJVuosakVODI0LyqrA5MXFWgJYscYmgOSL3VqXezUdOSyMYxL");

    return a.exec();
}

