#include "canvasconnection.h"
#include <QCoreApplication>
#include <QFileInfo>
#include <QString>
#include <vector>
#include <map>
#include <iostream>

using namespace std;


vector<QString> userid;
vector<double> assignmentid;
vector<double> assignmentscore;
map<double, vector<double> > everyAss;
vector<double> AssId;
vector<QString> submissionName;
vector<QString> downloadAdd;
vector<QString> fileAddress {"1.json","2.json","3.json","4.json" ,"5.json","6.json" ,"7.json","8.json" ,"9.json","0.json"  };
vector<QString> filenames { "20089.json" ,"20168.json","20285.json","19880.json","22347.json","19850.json","20383.json"};
vector<QString> student{"https://sit.instructure.com/api/v1/courses/10300000000000133/analytics/users/10300000000020089/assignments?access_token=1030~y2v695pyuP5tf7SbJVuosakVODI0LyqrA5MXFWgJYscYmgOSL3VqXezUdOSyMYxL",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/analytics/users/10300000000020168/assignments?access_token=1030~y2v695pyuP5tf7SbJVuosakVODI0LyqrA5MXFWgJYscYmgOSL3VqXezUdOSyMYxL",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/analytics/users/10300000000020285/assignments?access_token=1030~y2v695pyuP5tf7SbJVuosakVODI0LyqrA5MXFWgJYscYmgOSL3VqXezUdOSyMYxL",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/analytics/users/10300000000019880/assignments?access_token=1030~y2v695pyuP5tf7SbJVuosakVODI0LyqrA5MXFWgJYscYmgOSL3VqXezUdOSyMYxL",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/analytics/users/10300000000022347/assignments?access_token=1030~y2v695pyuP5tf7SbJVuosakVODI0LyqrA5MXFWgJYscYmgOSL3VqXezUdOSyMYxL",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/analytics/users/10300000000019850/assignments?access_token=1030~y2v695pyuP5tf7SbJVuosakVODI0LyqrA5MXFWgJYscYmgOSL3VqXezUdOSyMYxL",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/analytics/users/10300000000020383/assignments?access_token=1030~y2v695pyuP5tf7SbJVuosakVODI0LyqrA5MXFWgJYscYmgOSL3VqXezUdOSyMYxL"
                       };
vector<QString> fileApi{"https://sit.instructure.com/api/v1/courses/10300000000000133/assignments/10300000000000860/submissions?access_token=1030~ITJlnLeBaoqbzneuPAfdNLG5e9jAZqVHMiZWxF3FbvTG31U6l5adkBJcqOf8lCIO",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/assignments/10300000000046024/submissions?access_token=1030~ITJlnLeBaoqbzneuPAfdNLG5e9jAZqVHMiZWxF3FbvTG31U6l5adkBJcqOf8lCIO",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/assignments/10300000000061939/submissions?access_token=1030~ITJlnLeBaoqbzneuPAfdNLG5e9jAZqVHMiZWxF3FbvTG31U6l5adkBJcqOf8lCIO",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/assignments/10300000000046025/submissions?access_token=1030~ITJlnLeBaoqbzneuPAfdNLG5e9jAZqVHMiZWxF3FbvTG31U6l5adkBJcqOf8lCIO",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/assignments/10300000000046026/submissions?access_token=1030~ITJlnLeBaoqbzneuPAfdNLG5e9jAZqVHMiZWxF3FbvTG31U6l5adkBJcqOf8lCIO",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/assignments/10300000000061017/submissions?access_token=1030~ITJlnLeBaoqbzneuPAfdNLG5e9jAZqVHMiZWxF3FbvTG31U6l5adkBJcqOf8lCIO",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/assignments/10300000000061018/submissions?access_token=1030~ITJlnLeBaoqbzneuPAfdNLG5e9jAZqVHMiZWxF3FbvTG31U6l5adkBJcqOf8lCIO",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/assignments/10300000000061019/submissions?access_token=1030~ITJlnLeBaoqbzneuPAfdNLG5e9jAZqVHMiZWxF3FbvTG31U6l5adkBJcqOf8lCIO",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/assignments/10300000000061020/submissions?access_token=1030~ITJlnLeBaoqbzneuPAfdNLG5e9jAZqVHMiZWxF3FbvTG31U6l5adkBJcqOf8lCIO",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/assignments/10300000000061022/submissions?access_token=1030~ITJlnLeBaoqbzneuPAfdNLG5e9jAZqVHMiZWxF3FbvTG31U6l5adkBJcqOf8lCIO"
                       };




int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);
    canvasConnection A;
    // Download json file of every students
    A.doDownload();
    // Extract useful information (scores of every assignments)
    A.extract();
    // Put score in a hashmap
    A.everyAssScore();
    // Download json file of every assignments
    A.downAssignment();
    // Extract download url from json file
    A.readAttachment();
    cout << student.size() << endl;
    cout << fileApi.size() << endl;
    for(int j = 0; j < fileApi.size(); ++j){
        for(int i = 0; i < student.size(); ++i){
        cout << "assignmentid = " << assignmentid[j] << endl;
        cout << "score = " << everyAss[assignmentid[j]][i] << endl;
        }
    }
    for(vector<QString>::iterator it = submissionName.begin(); it != submissionName.end(); ++it){
        QString t = *it;
        cout << t.toStdString() << endl;
    }


    vector<QString>::iterator it = downloadAdd.begin();
    // Download students' submissions
    it += 7;
    A.doDownload(*it);
    return a.exec();
}


