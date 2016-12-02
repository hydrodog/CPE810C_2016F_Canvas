#ifndef CURVING_H
#define CURVING_H

#include <math.h>
#include <iostream>
#include <vector>
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
};

#endif // CURVING_H
