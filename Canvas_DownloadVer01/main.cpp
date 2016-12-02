#include "canvasconnection.h"
#include <QCoreApplication>
#include <QFileInfo>
using namespace std;

//TODO:download JSON file then put data into datd-base.
int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);
    canvasConnection A;
    canvasConnection B;
    canvasConnection C;
    A.setFilename("20168.json");
    A.sendRequest("https://canvas.instructure.com/api/v1/courses/10300000000000133/analytics/users/10300000000020168/assignments"
                  "?access_token=1030~ITJlnLeBaoqbzneuPAfdNLG5e9jAZqVHMiZWxF3FbvTG31U6l5adkBJcqOf8lCIO");
    B.setFilename("20285.json");
    B.sendRequest("https://canvas.instructure.com/api/v1/courses/10300000000000133/analytics/users/10300000000020285/assignments"
                  "?access_token=1030~ITJlnLeBaoqbzneuPAfdNLG5e9jAZqVHMiZWxF3FbvTG31U6l5adkBJcqOf8lCIO");
    A.readJson();
    std::cout << "*************************&&&&&&&&&&&&&&&&&******************************" << endl;
    B.readJson();
    return a.exec();
}
