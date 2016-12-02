#include "curving.h"
#include <math.h>
#include <iostream>
using namespace std;

int main()
{
    double mean=0;
    double variance=0;
    int length = 10;
    double data[length] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    Curving c(data, length);
    c.linCurve(10);
    c.statisticsoflin(mean,variance);

    double mean1=0;
    double variance1=0;
    int length2 = 5;
    double data2[length2] = {30, 40, 50, 60, 70};
    Curving c2(data2, length2);
    c2.rootCurve();
    c2.statisticsofroot(mean1,variance1);
    //c.m_curvedGrades;
    //c2.m_curvedGrades;

    double* curvedData1 = c2.m_curvedGrades;
    double* curvedData = c.m_curvedGrades;;

   for(int i =0; i < length; i++)
        cout << curvedData[i] << '\t';
    cout << '\n';

   for(int i =0; i < length2; i++)
        cout << curvedData1[i] << '\t';
    cout << '\n';

    if (variance < variance1){
        cout << "Choose linecurve." << endl;
    }else{
        cout <<"Choose rootcurve"<<endl;
    }

}
