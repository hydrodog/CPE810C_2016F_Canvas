#include "curving.h"


int main()
{
    vector<double> data;
    for(int i = 50; i <= 100; i+=10)
        data.push_back(i);

    //cout << data[2] << '\n';

    Curving c(data);
    /*
    c.linCurve(10);
    c.acceptChanges();
    data = c.returnCurve();
    cout << data[2] << '\n';

    c.rootCurve();
    c.acceptChanges();
    data = c.returnCurve();
    cout << data[2];
    */

    c.performCurve();
    data = c.returnCurve();
    for(int i = 0; i < data.size(); i++)
        cout << data[i] << '\t';
}
