#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Assignment.hh"
#include "Assignment_Unzip.hh"
#include "../Curving/curving.cpp"
#include "../Canvas_Update/CanvasUpdate/canvasupdate.h"

using namespace std;

//class Assignment;
//struct Student;

/*
struct grade_information
{
    double stu_id;
    string sub_comment;
    double sub_grade;

    grade_information(double stu_id, double sub_grade, string sub_comment) :
        stu_id(stu_id), sub_grade(sub_grade), sub_comment(sub_comment) {}
};
*/

class Course
{
    private:
        long m_course_id; //course id
        string m_course_name; //course name
        string m_course_code; //course code, i.e. EE810
        long m_account_id; //ADD SOMETHING
        Student *stu = new Student[5];//array of students in the course (each student is a student object), there is a set number of students for now
        int num_students_in_class = 5; //place holder, we will need to get this information from canvas, add method to set this value

    public:
        //Course object constructor
        Course(int course_id, string course_name, string course_code, long account_id) :
            m_course_id(course_id), m_course_name(course_name), m_course_code(course_code), m_account_id(account_id)
        {
            //gets the list of students in the class upon constructing the course object
            getStudents();
        }

        //gets the list of students in a given course from canvas
        //store infomation in Student array stu
        //get information from download team
        void getStudents()
        {
            double student_id[5] = {5902, 5126, 5498, 4712, 6912}; // the ID numbers of the students
            const char *student_name[5] = {"Sheng Hsu", "Suyog Deshmuk", "Zachary Binger", "Dov Kruger", "Marc Greenfield"};    // student's name which has to be english
            const char *student_email[5] = {"sheng@stevens.edu", "suyog@stevens.edu", "zbinger@stevens.edu", "dov.kruger@gmail.com", "marc@stevens.edu"}; //student e-mail addresses

            //currently uses preset data
            for (int i = 0; i < num_students_in_class; i++)
            {
                stu[i].S_info.Stu_ID = student_id[i]; //set the student ID
                stu[i].S_info.Stu_Name = student_name[i]; //set the student name
                stu[i].S_info.Stu_Mail_Addr = student_email[i]; //set the student e-mail address

                //testing
                //cout << "Student " << i << ": " << student_id[i] << " " << student_name[i] << " " << student_email[i] << endl;
            }
        }

        //this is called after an assignment is chosen
        //sets the file name attribute of the student object from the submission object for that student for the chosen assignment
        void getFileInfo(Submission s, Student & stu)
        {
            //fill in file info for each student object
            stu.F_info.File_name_Origin = s.getFileName();
            stu.F_info.file_number = s.getSubmissionNum();
        }

        //gets all of the assignments for the given course
        //returns a vector of assignment objects
        vector<Assignment>  getAssignments()
        {
            //List assignments
            //GET /api/v1/courses/:course_id/assignments
            //get each assignment, and store the info within each student object - students have an assignment subclass

            //1 - Get all assignments
            //fake vector of 3 assignments for testing
            vector<Assignment> assignment_vect;
            Assignment assignment1(1, 10311, 0);
            assignment_vect.push_back(assignment1);
            Assignment assignment2(2, 10311, 0);
            assignment_vect.push_back(assignment2);
            Assignment assignment3(3, 10311, 0);
            assignment_vect.push_back(assignment3);

            return assignment_vect;
        }

        //sets assignment attributes of student object based on the chosen assignment for the given course
        Assignment addAssignmentToStudents()
        {
            //get all of the assignments and store it in a vector
            vector<Assignment> assignment_vect = getAssignments();
            //assignment object to be set to the chosen assignment
            Assignment assignment;

            //prompt grader to choose which assignment to grade
            cout << "Which assignment would you like to grade? (Please enter the assignment number)\n";

            //list all assignments for the given course
            for (std::vector<Assignment>::iterator it = assignment_vect.begin(); it != assignment_vect.end(); ++it)
            {
                cout << *it;
            }
            long chosen_assignment = 0;
            bool correct_name = true;

            //grader chooses assignment based on assignment number
            while (correct_name)
            {
                correct_name = false;
                cin >> chosen_assignment;
                for (std::vector<Assignment>::iterator it = assignment_vect.begin(); it != assignment_vect.end(); ++it)
                {
                    if (chosen_assignment == it->get_assignment_id())
                    {
                        correct_name = true;
                        assignment = *it;
                        break;
                    }
                }
                if (correct_name)
                {
                    cout << endl;
                    break;
                }
                else //bad input
                {
                    cout << "Invalid assignment id. Please enter a valid assignment id.\n";
                    chosen_assignment = 0;
                    correct_name = true; //so while loop can continue
                }
            }

            //START HERE
            //Need this information from canvas - set to values for now
            const char *comment = "comment";
            const char *graph_title = "title";
            const char *title = "Assignment";
            long assignment_id = assignment.get_assignment_id(); //random number
            long course_id = assignment.get_course_id(); //random number
            //double m_grade; //changes after grading

            //sets assignment and submission info for student object
            for (int i = 0; i < num_students_in_class; i++)
            {
                stu[i].A_info.Assigment_Comment = comment;
                stu[i].A_info.Assignment_Graph_Title = graph_title;
                stu[i].A_info.Assignment_Title = title;
                stu[i].A_info.assignment_id = assignment_id;
                stu[i].A_info.course_id = course_id;
                //adds submission details to student object
                //may not need this
                //getFileInfo(assignment.getSubmission("USER", stu->S_info.Stu_ID), stu[i]);

                //cout << "Student " << i << ": course - " << stu[i].A_info.course_id << ", assignment - " << stu[i].A_info.assignment_id << endl;
            }
            //at this point, each student object has all the information about the current assignment
            //next step -> iterate through each student, and grade the submission
            return assignment;
        }

        //iterate through array of students, and grade their assignment submissions
        //takes in grader_username for file path
        void gradeStudents(string grader_username)
        {
            //student objects have assigment info, but not assignment objects
            Assignment assignment = addAssignmentToStudents();
            vector<double> grades; //used for each assignment, cleared after each use
            vector<grade_information> grade_objects;
            for (int i = 0; i < num_students_in_class; i++)
            {
                //get assignment submission and grade it
                //get submission from object, based on student id

                //problem - grading the submission file listed in the student object
                    //but where does the students object get it from?
                //get the submission based on the id of the student
                cout << "Output for student: " << i + 1 << ", ID: " << stu[i].S_info.Stu_ID << endl;


                Submission s = assignment.getSubmission("Test.cpp", grader_username, stu[i].S_info.Stu_ID);
                stu[i].S_info.Stu_Assigment_Grade_Current = s.grade();
                stu[i].A_info.Assigment_Comment = s.grade_comment();
                s.upload(); //upload grade to canvas, maybe just do once at end for everyone
                grades.push_back((double)stu[i].S_info.Stu_Assigment_Grade_Current);
                grade_objects.push_back(grade_information(stu[i].S_info.Stu_ID, stu[i].S_info.Stu_Assigment_Grade_Current, stu[i].A_info.Assigment_Comment));
            }

            cout << endl;
            //Display grades before curving
            for (int i = 0; i < num_students_in_class; i++)
            {
                cout << "Student " << i + 1 << ", " <<  stu[i].S_info.Stu_Name << ": " << stu[i].S_info.Stu_Assigment_Grade_Current << endl;
            }

            cout << endl << endl;

            //curve grades
            Curving curve(grades);

            curve.performCurve();
            grades = curve.returnCurve(); //saves curved grades in the vector
            //reinput curved grades
            for (int i = 0; i < num_students_in_class; i++)
            {
                stu[i].S_info.Stu_Assigment_Grade_Current = grades[i];
                grade_objects[i].posted_grade = grades[i];
            }

            cout << "\nUploading to Canvas:" << endl;

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

        //testing
        void showStudentGradesAndComments()
        {
            cout << "\nGRADES AND COMMENTS AFTER GRADING" << endl;
            for (int i = 0; i < num_students_in_class; i++)
            {
                cout << "Student " << i + 1 << ", ID: " << stu[i].S_info.Stu_ID
                     << " - Grade: " << stu[i].S_info.Stu_Assigment_Grade_Current << ", Comment: " << stu[i].A_info.Assigment_Comment << endl;
            }
        }

        //testing
        void getAssignmentsFromStudent()
        {
            cout << std::endl;
            for (int i = 0; i < num_students_in_class; i++)
            {
                cout << "Student " << i << ": " << stu[i].S_info.Stu_ID << " " << stu[i].S_info.Stu_Name << " " << stu[i].S_info.Stu_Mail_Addr << endl;
                //***might need to get all assignments, right now if can only get one assignment because of the construction of the Student struct
                cout << "\tAssignment: " << "Title: " << stu[i].A_info.Assignment_Title << ", Course ID: " << stu[i].A_info.course_id << ", Assignment ID: " << stu[i].A_info.assignment_id << ", Comment: " << stu[i].A_info.Assigment_Comment << ", Graph Title: " << stu[i].A_info.Assignment_Graph_Title << endl;
                //studend name at the end is to ensure this submission corresponds to the correct student
                cout << "\t\tSubmission: " << "File Name: \'" << stu[i].F_info.File_name_Origin << "\', Submission Number: " << stu[i].F_info.file_number << ", Submitter (student): " << stu[i].S_info.Stu_Name << endl;
            }
        }
};


#endif // COURSE_HH
