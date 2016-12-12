#include <QCoreApplication>
#include <canvasupdate.h>

QString test_auth = "Bearer 1030~4MvxMX4ZFH8LCUAe9pFKhNUwFc6o4PnsFny5vlO4sLdyExxx3B9SR3ULM2nzl211";

grade_info stdtemp[3] = {
    {"7672","bad job!!!!!","3"},
    {"19850","bad job too!!!!!!","3"},
    {"19880","You are much worse!!!!!!","33"}
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
//    Canvas_Update update2("133","46024", "test");
//    update2.setAuthByFile("auth.txt");
//    update2.addSingle("7672","just joke","59");

    return a.exec();
}
