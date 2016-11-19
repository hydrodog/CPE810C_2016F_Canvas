#ifndef STUDENT_H
#define STUDENT_H

#include <vector>
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
protected:
    std::vector<double> Assignment_Marks;
    std::vector<double> Test_Marks;
public:
    Student();
    //~Student();
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
};
#endif // STUDENT_H
