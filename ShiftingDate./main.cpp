#include<iostream>
#include <cmath>
#define PI 3.1415926
using namespace std;

int main()
{
    double r=1;
    int n;
    for(n=3;n<=10;n++)
    {
         r=r/cos(PI/n);

    }
    cout<<"radius for n=10 is :"<<r<<endl;
    r=1;
    for(n=3;n<=100;n++)
    {
         r=r/cos(PI/n);

    }
    cout<<"radius for n=100 is :"<<r<<endl;
    r=1;
    for(n=3;n<=1000;n++)
    {
         r=r/cos(PI/n);

    }
    cout<<"radius for n=1000 is :"<<r<<endl;
    r=1;
    for(n=3;n<=10000;n++)
    {
         r=r/cos(PI/n);

    }
    cout<<"radius for n=10000 is :"<<r<<endl;
    r=1;
    for(n=3;n<=100000;n++)
    {
         r=r/cos(PI/n);

    }
    cout<<"radius for n=100000 is :"<<r<<endl;
    r=1;
    for(n=3;n<=1000000;n++)
    {
         r=r/cos(PI/n);

    }
    cout<<"radius for n=1000000 is :"<<r<<endl;
    return 0;
}
