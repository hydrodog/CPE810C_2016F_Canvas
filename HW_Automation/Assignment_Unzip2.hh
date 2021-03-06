#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Assignment.hh"
#include "Assignment_Unzip.hh"
using namespace std;

//class Assignment;
//struct Student;

class Course
{
    private:
        long m_course_id;
        string m_course_name;
        string m_course_code;
        long m_account_id;
        //long m_student_id;
        Student *stu = new Student[5];//course object contains the list of students in the course (each student is a student object)
        int num_students_in_class = 5; //place holder, we will need to get this information from canvas, add method to set this value

        //need an array of students - each student contains information, file, and assignment

        //string m_student_name;

    public:
        Course(int course_id, string course_name, string course_code, long account_id) :
            m_course_id(course_id), m_course_name(course_name), m_course_code(course_code), m_account_id(account_id) {}

        //gets the list of students in a given course from canvas
        //store infomation in Student array stu
        //get information from download team
        void getStudents()
        {
            //might need a constructor for Studentt object
            double student_id[5] = {1231, 1232, 1233, 1234, 1235};           // the ID number of student
            const char *student_name[5] = {"Sheng", "Suyog", "Zac", "Dov", "Marc"};    // student's name which has to be english
            const char *student_email[5] = {"sheng@stevens.edu", "suyog@stevens.edu", "zac@stevens.edu", "dov@stevens.edu", "marc@stevens.edu"};

            //set information for each student
            for (int i = 0; i < num_students_in_class; i++)
            {
                stu[i].S_info.Stu_ID = student_id[i];
                stu[i].S_info.Stu_Name = student_name[i];
                stu[i].S_info.Stu_Mail_Addr = student_email[i];

                //testing
                //cout << "Student " << i << ": " << student_id[i] << " " << student_name[i] << " " << student_email[i] << endl;
            }
        }

        void getFileInfo(Submission s, Student & stu)
        {
            //fill in file info for each student object
            stu.F_info.File_name_Origin = s.getFileName();
            stu.F_info.file_number = s.getSubmissionNum();
        }

        vector<Assignment>  getAssignments()
        {
            //List assignments
            //GET /api/v1/courses/:course_id/assignments
            //get each assignment, and store the info within each student object - students have an assignment subclass

            //1 - Get all assignments
            //fake vector of assignments for testing
            vector<Assignment> assignment_vect;
            Assignment assignment1(125, 10311, 0);
            assignment_vect.push_back(assignment1);
            Assignment assignment2(126, 10311, 0);
            assignment_vect.push_back(assignment2);
            Assignment assignment3(127, 10311, 0);
            assignment_vect.push_back(assignment3);

            //2 - Put Assignment info in each student object
            for (std::vector<Assignment>::iterator it = assignment_vect.begin(); it != assignment_vect.end(); ++it)
            {
                //display the assignments
                //cout << "Assignment: " << it->get_assignment_id() << " " << it->get_course_id() << " " << it->getGrade() << endl;
                cout << *it; //outputs the assignment
                //fill in file info in student object (same as submission info)
                cout << "\t" << it->getSubmission(); //outputs the corresponding submission

                //for each assignment object, get the information needed to input to the student object

                //Need this information from canvas - set to values for now
                const char *comment = "comment";
                const char *graph_title = "title";
                const char *title = "Assignment";
                long assignment_id = it->get_assignment_id(); //random number
                long course_id = it->get_course_id(); //random number
                //double m_grade; //changes after grading

                //sets assignment and submission info for student object
                for (int i = 0; i < num_students_in_class; i++)
                {
                    stu[i].A_info.Assigment_Comment = comment;
                    stu[i].A_info.Assignment_Graph_Title = graph_title;
                    stu[i].A_info.Assignment_Title = title;
                    stu[i].A_info.assignment_id = assignment_id;
                    stu[i].A_info.course_id = course_id;
                    getFileInfo(it->getSubmission(), stu[i]);
                }
            }
            return assignment_vect;
        }

        //testing
        void getAssignmentsFromStudent()
        {
            cout << std::endl;
            for (int i = 0; i < num_students_in_class; i++)
            {
                cout << "Student " << i << ": " << stu[i].S_info.Stu_ID << " " << stu[i].S_info.Stu_Name << " " << stu[i].S_info.Stu_Mail_Addr << endl;
                //***might need to get all assignments, right now if can only get one assignment because of the construction of the Student struct
                cout << \t << "Assignment: " << "Title: " << stu[i].A_info.Assignment_Title << ", Course ID: " << stu[i].A_info.course_id << ", Assignment ID: " << stu[i].A_info.assignment_id << ", Comment: " << stu[i].A_info.Assigment_Comment << ", Graph Title: " << stu[i].A_info.Assignment_Graph_Title << endl;
                //studend name at the end is to ensure this submission corresponds to the correct student
                cout << \t\t <<"Submission: " << "File Name: \'" << stu[i].F_info.File_name_Origin << "\', Submission Number: " << stu[i].F_info.file_number << ", Submitter (student): " << stu[i].S_info.Stu_Name << endl;
            }
        }

        //public get methods
        string getCourseName()
        {
            return m_course_name;
        }

        long getCourseID()
        {
            return m_course_id;
        }

        string getCourseCode()
        {
            return m_course_code;
        }

        long getAccountID()
        {
            return m_account_id;
        }

};


#endif // COURSE_HH

