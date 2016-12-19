#ifndef STUDENT_H
#define STUDENT_H

#include <vector>
#include <algorithm>
#include <stdio.h>
#include <iostream>
/* Student class is to claculate the AVERAGE grade of a STUDENT in all the assignments,
   all the Tests, Project, Quizzes etc..
 * To get the marks of different assignments of a student.
 * TODO: Have to define destructor.
*/

class Student{
private:
    int student_id;
    static int Assignment_type;  //to know what type of assignment it is eg: Test or a Homework assignment
    double StudentGradeSheet[]; // grade in the course till this assignment
    static int numAssignments;
    static int numTests;
    int scoreInterval[21]={0};
public:
    Student();
    //~Student();
    std::vector<double> Assignment_Marks;
    std::vector<double> Test_Marks;
    void Setstudent_id(int id);
    int Getstudent_id();
    void SetAssignment_Marks(double Marks);
    std::vector<double> Get_Marks() const;
    void SetTest_Marks(double marks);
    std::vector<double> Get_TestMarks() const;
    static int Get_numAssignments();
    static int Get_numTests();
    static void Set_numTests();
    static int GetAssignment_type(void);
    static void Set_AssignmentType(int type);
    static void Set_numAssignments();
    double Assignment_Mean();
    double Test_Mean();
    double overall_Mean();
    void Assignment_Arrange_LtoH();
    void Test_Arrange_LtoH();
    double Assignment_Median();
    double Test_Median();
    void setAssignment_Interval();
    int getAssignment_Interval(int i);
    //void print();
};
#endif // STUDENT_H
