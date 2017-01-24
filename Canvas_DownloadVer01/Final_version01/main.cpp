#include "canvasconnection.h"
#include <QCoreApplication>
#include <QFileInfo>
#include <QString>
#include <vector>
using namespace std;

//TODO:download JSON file from Canvas and then put data into datd-base.


vector<QString> student{"https://canvas.instructure.com/api/v1/courses/10300000000000133/analytics/users/10300000000020089/assignments?access_token=",
                        "https://canvas.instructure.com/api/v1/courses/10300000000000133/analytics/users/10300000000020168/assignments?access_token=",
                        "https://canvas.instructure.com/api/v1/courses/10300000000000133/analytics/users/10300000000020285/assignments?access_token=",
                        "https://canvas.instructure.com/api/v1/courses/10300000000000133/analytics/users/10300000000019880/assignments?access_token=",
                        "https://canvas.instructure.com/api/v1/courses/10300000000000133/analytics/users/10300000000007672/assignments?access_token=",
                        "https://canvas.instructure.com/api/v1/courses/10300000000000133/analytics/users/10300000000019850/assignments?access_token=",
                        "https://canvas.instructure.com/api/v1/courses/10300000000000133/analytics/users/10300000000020383/assignments?access_token="};



vector<QString> filenames { "20089.json" ,"20168.json","20285.json","19880.json","07672.json","19850.json","20383.json"};


vector<QString> userid;   //store userid
vector<QString> assignmentid;   //store assignmentid
vector<QString> assignmentscore;   //store assignmentscore;



int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);
    canvasConnection A;
    A.doDownload();
    A.extract();
    A.showdata();


/*  we also have other functions for other groups
    A.setFilename();
    A.sendRequest();
    A.readjson();
*/
    return a.exec();
}


