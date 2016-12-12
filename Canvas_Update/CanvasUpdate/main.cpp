#include <QCoreApplication>
#include <canvasupdate.h>


QString test_auth = "Bearer 1030~4MvxMX4ZFH8LCUAe9pFKhNUwFc6o4PnsFny5vlO4sLdyExxx3B9SR3ULM2nzl211";

grade_info stdtemp[3] = {
        {"7672","bad job!!!!!","0"},
        {"19850","bad job too!!!!!!","0"},
        {"19880","You are much worse!!!!!!","0"}
        };



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    vector<grade_info> gradelists;
    for(int i=0;i<3;i++)
    {
        gradelists.push_back(stdtemp[i]);
    }
    Canvas_Update update1(gradelists,"133","46024",test_auth);
    update1.sendRequest();
    return a.exec();
}
