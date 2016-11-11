#include "canvasconnection.h"
#include <QCoreApplication>
using namespace std;
//TODO:download JSON file then put data into datd-base.
int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);
    canvasConnection A;
    canvasConnection B;
    A.sendRequest("https://canvas.instructure.com/api/v1/courses?access_token=1030~y2v695pyuP5tf7SbJVuosakVODI0LyqrA5MXFWgJYscYmgOSL3VqXezUdOSyMYxL");
    B.sendRequest("https://google.com");
    return a.exec();
}

