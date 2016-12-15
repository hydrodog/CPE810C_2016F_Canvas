#ifndef CURVING_H
#define CURVING_H

#include <math.h>
#include <iostream>
#include <vector>
#include <QString>
using namespace std;

/*
  @author: Thomas Falsone
  @modified:

  The objective of this group is to take input data, curve the data for the user,
  ask for confirmation, then push the changes back into Canvas
*/

/*
  This class is used to take grades and curve them based on the needs of the user
*/


class Curving {
private:
    int m_size;
    vector<double> m_curvedGrades;
    vector<double> m_originalGrades;
    bool m_confirm;
    bool m_typeCurve;
public:
    Curving(vector<double> data);
    void linCurve(double curve);
    void rootCurve();
    vector<double> returnCurve() const;
    void acceptChanges();
    int getMeanOrig();
    int getStdDevOrig();
    int getMeanCur();
    int getStdDevCur();
    void performCurve();
};

#endif // CURVING_H
