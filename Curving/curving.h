#ifndef CURVING_H
#define CURVING_H

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
    double* m_curvedGrades;
    double* m_originalGrades;
    bool m_confirm;
public:
    Curving(double* data, int size);
    void linCurve(int curve);
    void rootCurve();
    double* returnCurve() const;
    void acceptChanges();
};

#endif // CURVING_H
