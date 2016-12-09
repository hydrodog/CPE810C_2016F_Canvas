#ifndef SUBMISSION_H
#define SUBMISSION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Submission
{
    private:
        string m_file_name;
        long m_assignment_id;
        //Assignment m_assignment;
        long m_course_id;
        //Course m_course;
        int m_submission_num; //submission attempt number
        //long m_student_id;
        int m_grader_id;
        double m_grade; //number grades, not letter grades
        string m_grader_comment = "";
        bool m_late;
        //bool excused; //if not completed, it doesn't affect the grade
        stringstream open_sub, compile_sub, run_sub;
        string m_grader_username; //determines the path used to get to the submission file
                                //ex. "C:/Users/" << m_grader_username << "/Desktop/git/CPE810C_2016F_Canvas/HW_Automation/submission_file/assignment_" << m_assignment_id << "/Test.exe&"
        double m_student_id;

    public:

        Submission(string file_name, long assignment_id, long course_id, int submission_num, int grader_id, double grade, bool late, string grader_username, double student_id)
            : m_file_name(file_name), m_assignment_id(assignment_id), m_course_id(course_id), m_submission_num(submission_num), m_grader_id(grader_id), m_grade(grade), m_late(late), m_grader_username(grader_username), m_student_id(student_id) {}

        friend ostream& operator <<(ostream& s, Submission sub)
        {
            return s << "Submission #" << sub.m_submission_num << ", File Name: \'" << sub.m_file_name << "\': Assignment " << sub.m_assignment_id << ", Course " << sub.m_course_id << ", Grader ID: " << sub.m_grader_id << ", Grade: " << sub.m_grade << ", Comments: " << sub.m_grader_comment << std::endl;
        }

        string getFileName()
        {
            return m_file_name;
        }

        long getAssignmentID()
        {
            return m_assignment_id;
        }

        long getCourseID()
        {
            return m_course_id;
        }

        int getSubmissionNum()
        {
            return m_submission_num;
        }

        int getGraderID()
        {
            return m_grader_id;
        }

        double getGrade()
        {
            return m_grade;
        }

        string getGraderComment()
        {
            return m_grader_comment;
        }

        bool getLate()
        {
            return m_late;
        }

        //TODO: get public methods from upload and download team so that we can download a submission and then upload a grade

        //TODO: get download method from other group
        //downloads the submitted file from a submissions object
        void download() {}

        //opens and displays file/source code from the submissions object
        void display_source_code()
        {
            //open submission file
            //for now, assume it's windows
            //may need to change file path in the future
            //open_sub << "atom.cmd submission_files/assignment_" << m_assignment_id << "Test.cpp&";
            open_sub << "C:/Users/" << m_grader_username << "/Desktop/git/CPE810C_2016F_Canvas/HW_Automation/submission_file/assignment_" << m_assignment_id << "/Test.cpp&";
            system(open_sub.str().c_str());
            //cout statement is for checking the path
            //cout << open_sub.str() << endl;
        }

        //compiles a submitted file, return true if compiles, return false if not compiled
        bool compile_submission()
        {
            //cout << "compile" << endl;
            compile_sub << "g++ -std=c++11 C:/Users/" << m_grader_username << "/Desktop/git/CPE810C_2016F_Canvas/HW_Automation/submission_file/assignment_" << m_assignment_id << "/" << m_student_id << "/Test.cpp";
            compile_sub << " -o C:/Users/" << m_grader_username << "/Desktop/git/CPE810C_2016F_Canvas/HW_Automation/submission_file/assignment_" << m_assignment_id << "/Test";
            //cout statement is for checking the path
            //cout << compile_sub.str() << endl;
            //cout << compile_sub.str() << endl;
            system(compile_sub.str().c_str());
            return true;
        }

        //runs a submitted file, returns true if run, returns false, if not run
        bool run_submission()
        {
            //cout << "run" << endl;
            run_sub << "C:/Users/" << m_grader_username << "/Desktop/git/CPE810C_2016F_Canvas/HW_Automation/submission_file/assignment_" << m_assignment_id << "/" << m_student_id << "/Test.exe&";
            //cout statement is for checking the path
            //cout << run_sub.str() << endl;
            system(run_sub.str().c_str());
            return true;
        }

        //grades a submitted file, giving 50 points is it compiles and another 50 points if it runs. If neither, it gives a score of 25.
        double grade()
        {
            double grade = 0;
            bool compiled = compile_submission();
            if (compiled)
            {
                grade += 75;
                bool ran = run_submission();
                if (ran)
                {
                    grade += 25;
                }
            }

            m_grade = grade;
            return grade;
        }

        //returns grade entered by the grader, if he chooses to overwrite the default grade
        double overwrite_grade(double grade)
        {
            m_grade = grade;
            return grade;
        }

        //adds a comment from the grader to the submission file
        string grade_comment(string comment)
        {
            m_grader_comment = comment;
            return comment;
        }

        //TODO: Get function from plagiarism detector group
        //returns a similarity score between the submitted file and other files
        double plag_detector()
        {
            return 0;
        }

        void setGraderUsername(string name)
        {
            m_grader_username = name;
        }

        //TODO: Get upload function from upload group
        //uploads a grade and possibly a comment to the submission object
        void upload()
        {
            // data needed for upload
                //course id -> long m_course_id
                //assignment id -> long m_assignment_id
                //student id -> double m_student_id
                //grade -> double m_grade
                //comment -> string m_grader_comment
                //grader id (author) -> string m_grader_username or int m_grader_id
            cout << "Course ID: "
                 << m_course_id << ", Assigment ID: "
                 << m_assignment_id << ", Student ID: "
                 << m_student_id << ", Assignment Grade: "
                 << m_grade << ", Assignment Comment: "
                 << m_grader_comment << ", Grade ID: "
                 << m_grader_id << endl;
        }
};


#endif // SUBMISSION_HH
