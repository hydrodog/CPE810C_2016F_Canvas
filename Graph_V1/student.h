#ifndef STUDENT_H
#define STUDENT_H

const int NUM_ASSIGNMENTS = 2;

/* Student class is to claculate the AVERAGE grade of a STUDENT in all the assignments,
   all the Tests, Project, Quizzes etc..
 * To get the marks of different assignments of a student.
 * TODO: Have to define destructor.
*/

class Student{
private:
    int student_id;
    static int Assignment_type;  //to know what type of assignment it is eg: Test or a Homework assignment
    double Marks[NUM_ASSIGNMENTS];
    double StudentGradeSheet[]; // grade in the course till this assignment
    static int numAssignments;
    static int numTests;

public:
    Student();
    //~Student();
    void Setstudent_id(int id);
    int Getstudent_id();
    void Set_Marks(int,double);
    double* Get_Marks();
    static int Get_numAssignments();
    static int Get_numTests();
    static void Set_numTests();
    static int GetAssignment_type(void);
    static void SetAssignmentType(int type);
    static void Set_numAssignments();

    // Class functions to claculate average grades
    double allAssignments_avg();
    double allTests_avg();
    double Final_Grade();
    double Project_grade();

};
#endif // STUDENT_H
