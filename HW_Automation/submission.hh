#ifndef SUBMISSION_H
#define SUBMISSION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "../Plagiarism_Detector_Ver01/PlagiarismDetector.cpp"
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
        double m_grade; //number grades, not letter grades, eventually make a double
        string m_grader_comment = "";
        bool m_late;
        //bool excused; //if not completed, it doesn't affect the grade
        stringstream open_sub, compile_sub, run_sub;
        string m_grader_username; //determines the path used to get to the submission file
                                //ex. "C:/Users/" << m_grader_username << "/Desktop/git/CPE810C_2016F_Canvas/HW_Automation/submission_file/assignment_" << m_assignment_id << "/Test.exe&"
        double m_student_id;
        string m_file_type; //file type, i.e. cpp, java, python
        string m_file_ext; //file extension

    public:

        Submission(string file_name, long assignment_id, long course_id, int submission_num, int grader_id, double grade, bool late, string grader_username, double student_id)
            : m_file_name(file_name), m_assignment_id(assignment_id), m_course_id(course_id), m_submission_num(submission_num), m_grader_id(grader_id), m_grade(grade), m_late(late), m_grader_username(grader_username), m_student_id(student_id) {}

        friend ostream& operator <<(ostream& s, Submission sub)
        {
            return s << "Submission #" << sub.m_submission_num << ", File Name: \'" << sub.m_file_name << "\': Assignment " << sub.m_assignment_id << ", Course " << sub.m_course_id << ", Grader ID: " << sub.m_grader_id << ", Grade: " << sub.m_grade << ", Comments: " << sub.m_grader_comment << std::endl;
        }

        //TODO: get download method from other group
        //downloads the submitted file from a submissions object
        void download() {}

        void check_file_type()
        {
            stringstream ss1;
            //iterator up until the period
            int index = 0; //index of period in file name
            for (unsigned int i = 0; i < m_file_name.size(); i++)
            {
                if (m_file_name[i] == '.')
                {
                    index = i;
                    break;
                }
                ss1 << m_file_name[i];
            }

            stringstream ss2;
            for (unsigned int i = index + 1; i < m_file_name.size(); i++)
            {
                //cout << m_file_name[i];
                ss2 << m_file_name[i];
            }
            if (ss2.str() == "py")
            {
                m_file_type = "python";
            }
            else if (ss2.str() == "java")
            {
                m_file_type = "java";
            }
            else if (ss2.str() == "cpp" || ss2.str() == "cc" || ss2.str() == "hh")
            {
                m_file_type = "c++";
            }
            else
            {
                //error message?
                //cout << "Not a valid file type. File: " << m_file_name << endl;
                m_file_type = "Error: Bad File Name";
            }
            //cout << "SS1 " << ss1.str() << endl;
            m_file_ext = ss2.str();
            m_file_name = ss1.str();
            //cout << "Ext: " << m_file_ext << endl;
            cout << "File Type: " << m_file_type << endl;
        }

        //opens and displays file/source code from the submissions object
        void display_source_code()
        {
            //open submission file
            //for now, assume it's windows
            //may need to change file path in the future
            //open_sub << "atom.cmd submission_files/assignment_" << m_assignment_id << "Test.cpp&";

            //cout << "OPEN" << endl;
            //cout << "NAME " << m_file_name << endl;
            open_sub << "C:/Users/" << m_grader_username << "/Desktop/git/CPE810C_2016F_Canvas/HW_Automation/submission_file/assignment_" << m_assignment_id << "/" << m_student_id << "/" << m_file_name << "." << m_file_ext << "&";
            //cout << open_sub.str() << endl;
            system(open_sub.str().c_str());
            //cout statement is for checking the path
            //cout << open_sub.str() << endl;
        }

        //compiles a submitted file, return true if compiles, return false if not compiled
        bool compile_submission()
        {
            if (m_file_type == "c++")
            {
                compile_sub << "g++ -std=c++11 C:/Users/" << m_grader_username << "/Desktop/git/CPE810C_2016F_Canvas/HW_Automation/submission_file/assignment_" << m_assignment_id << "/" << m_student_id << "/" << m_file_name << "." << m_file_ext;
                compile_sub << " -o C:/Users/" << m_grader_username << "/Desktop/git/CPE810C_2016F_Canvas/HW_Automation/submission_file/assignment_" << m_assignment_id << "/" << m_file_name;
            }

            else if (m_file_type == "java")
            {
                compile_sub << "javac -std=c++11 C:/Users/" << m_grader_username << "/Desktop/git/CPE810C_2016F_Canvas/HW_Automation/submission_file/assignment_" << m_assignment_id << "/" << m_student_id << "/" << m_file_name << "." << m_file_ext;
                //compile_sub << " -o C:/Users/" << m_grader_username << "/Desktop/git/CPE810C_2016F_Canvas/HW_Automation/submission_file/assignment_" << m_assignment_id << "/Test";
            }

            else if (m_file_type == "python")
            {
                cout << "Python file: cannot compile" << endl;
            }

            //compile_sub << "g++ -std=c++11 C:/Users/" << m_grader_username << "/Desktop/git/CPE810C_2016F_Canvas/HW_Automation/submission_file/assignment_" << m_assignment_id << "/" << m_student_id << "/Test.cpp";
            //compile_sub << " -o C:/Users/" << m_grader_username << "/Desktop/git/CPE810C_2016F_Canvas/HW_Automation/submission_file/assignment_" << m_assignment_id << "/Test";
            system(compile_sub.str().c_str());
            return true;
        }

        //runs a submitted file, returns true if run, returns false, if not run
        bool run_submission()
        {
            if (m_file_type == "c++")
            {
                run_sub << "C:/Users/" << m_grader_username << "/Desktop/git/CPE810C_2016F_Canvas/HW_Automation/submission_file/assignment_" << m_assignment_id << "/" << m_student_id << "/" << m_file_name;// <<".exe&";
            }

            else if (m_file_type == "java")
            {
                run_sub << "java C:/Users/" << m_grader_username << "/Desktop/git/CPE810C_2016F_Canvas/HW_Automation/submission_file/assignment_" << m_assignment_id << "/" << m_student_id << "/" << m_file_name;
            }

            else if (m_file_type == "python")
            {
                cout << "Python file: cannot run" << endl;
            }

            //run_sub << "C:/Users/" << m_grader_username << "/Desktop/git/CPE810C_2016F_Canvas/HW_Automation/submission_file/assignment_" << m_assignment_id << "/" << m_student_id << "/Test.exe&";
            system(run_sub.str().c_str());
            return true;
        }

        //grades a submitted file, giving 50 points is it compiles and another 50 points if it runs. If neither, it gives a score of 25.
        double  grade()
        {
            check_file_type(); //checkes file type and sets m_file_type to python, java, or c++
            display_source_code();
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
            cout << "Please enter grade: ";
            while (1)
            {
                string grade_string;
                istringstream iss;
                cin >> grade_string;
                iss.str(grade_string);
                if (!(iss >> grade)) //not a valid grade
                {
                    cout << "Please enter a valid number: ";
                }
                else
                {
                    break;
                }
            }
            m_grade = grade;
            if (m_student_id == 1231 || m_student_id == 1232)
            {
                plag_detector();
            }
            //string comment = grade_comment(); //this is called in the course class in the gradeStudents method
            //upload();
            return grade;
        }

        //returns grade entered by the grader, if he chooses to overwrite the default grade
        double overwrite_grade(double grade)
        {            
            m_grade = grade;
            return grade;
        }

        //adds a comment from the grader to the submission file
        string grade_comment()
        {
            cout << "Please enter any submission comments (if none, hit enter): ";
            string comment ;
            cin.ignore();
            getline(cin, comment);
            //char* comment = new char[200];
            //cin.getline(comment, 200);
            cout << endl;
            m_grader_comment = comment;
            return comment;
        }

        //TODO: Get function from plagiarism detector group
        //returns a similarity score between the submitted file and other files
        void plag_detector()
        {
            cout << "Plag Detector" << endl;
            stringstream s1;
            stringstream s2;

            //s1 << "C:/Users/" << m_grader_username << "/Desktop/git/CPE810C_2016F_Canvas/HW_Automation/submission_file/assignment_" << m_assignment_id << "/1231/" << m_file_name << "." << m_file_ext;
            s1 << "C:/Users/" << m_grader_username << "/Desktop/git/CPE810C_2016F_Canvas/HW_Automation/course.hh";
            s2 << "C:/Users/" << m_grader_username << "/Desktop/git/CPE810C_2016F_Canvas/HW_Automation/submission_file/assignment_" << m_assignment_id << "/1232/" << m_file_name << "." << m_file_ext;

            string file1 = s1.str();
            string file2 = s2.str();

            cout << file1 << endl;
            cout << file2 << endl;

            detectPlagiarism dp;
            cout << "PLAG: " << dp.quickFileComp(file1, file2) << endl;
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
            cout << "Uploading grades to canvas...\nCourse ID: "
                 << m_course_id << ", Assigment ID: "
                 << m_assignment_id << ", Student ID: "
                 << m_student_id << ", Assignment Grade: "
                 << m_grade << ", Assignment Comment: "
                 << m_grader_comment << ", Grader ID: "
                 << m_grader_id << endl << endl << endl;
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
};


#endif // SUBMISSION_HH
