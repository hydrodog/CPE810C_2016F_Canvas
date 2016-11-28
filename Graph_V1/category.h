#ifndef CATEGORY_H
#define CATEGORY_H
#include "student.h"
#include <algorithm>
#include <math.h>


class category:public Student
{
private:
    std::vector<double> sorted_Assignment=Assignment_Marks;
    std::vector<double> sorted_Test=Test_Marks;
public:
    category();
    //~category();
    double Assignment_Mean();
    double Test_Mean();
    double overall_Mean();
    void Assignment_Arrange_HtoL();
    void Test_Arrange_HtoL();
    double Assignment_Median();
    double Test_Median();
    double Assignment_Variance();
    double Test_Variance();
    //percentage
    //u
};

#endif // CATEGORY_H
