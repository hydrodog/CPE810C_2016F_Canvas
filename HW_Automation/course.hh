#ifndef COURSE_HH
#define COURSE_HH

#include <iostream>
#include <string>
#include <vector>
//#include "Assignment.hh"
//#include "Assignment_Unzip.hh"
using namespace std;

class Assignment;
struct Student;

class Course
{
    private:
        long m_course_id;
        string m_course_name;
        string m_course_code;
        long m_account_id;
        //long m_student_id;
        Student *stu = new Student[25];//course object contains the list of students in the course (each student is a student object)

        //need an array of students - each student contains information, file, and assignment

        //string m_student_name;

    public:
        Course(int course_id, string course_name, string course_code, long account_id) :
            m_course_id(course_id), m_course_name(course_name), m_course_code(course_code), m_account_id(account_id) {}

        //gets the list of students in a given course from canvas
        //get information from download team
        Student * getStudents()
        {
            int num_students_in_class = 25; //place holder, we will need to get this information from canvas
            //might need a constructor for Studentt object
            double student_id;           // the ID number of student
            const char *student_name;    // student's name which has to be english
            const char *student_email;

            //set information for each student
            for (int i = 0; i < num_students_in_class; i++)
            {
                stu[i]->Stu_ID = student_id;
                stu[i]->Stu_Name = student_name;
                stu[i]->Stu_Mail_addr = student_email;
            }
        }

        //may need to change return type
        void  getAssignments()
        {
            //List assignments
            //GET /api/v1/courses/:course_id/assignments
            //get each assignment, and store the info within each student object - students have an assignment subclass

            //1 - Get all assignments
            //fake vector of assignments for now
            vector<Assignment> assignment_vect;
            Assignment assignment(50, 125, 10311, 0);
            assignment_vect.push_back(assignment);
            return assignment_vect;

            //2 - Put Assignment info in each student object
            for (std::vector<Assignment>::iterator it = assignment_vect.begin(); it != assignment_vect.end(); ++it)
            {
                //for each assignment object, get the information needed to input to the student object

                //Need this information from canvas - set to values for now
                const char *comment = "";
                const char *graph_title = "";
                const char *title = "Assignment";
                long assignment_id = it->get_assignment_id(); //random number
                long course_id = it->get_course_id(); //random number
                //double m_grade; //changes after grading

                for (int i = 0; i < num_students_in_class; i++)
                {
                    stu[i]->Assignment_Comment = comment;
                    stu[i]->Assignment_Graph_Title = graph_title;
                    stu[i]->Assignment_Title = title;
                    stu[i]->assignment_id = assignment_id;
                    stu[i]->course_id = course_id;
                }
            }

        }


};


#endif // COURSE_HH
