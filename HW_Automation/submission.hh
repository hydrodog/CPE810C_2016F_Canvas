#ifndef SUBMISSION_H
#define SUBMISSION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
//#include "../Plagiarism_Detector_Ver01/PlagiarismDetector.cpp"
using namespace std;

class Submission
{
    private:
        string m_file_name; //submission file name
        long m_assignment_id; //assignment id
        long m_course_id; //course id
        int m_submission_num; //submission attempt number
        int m_grader_id; //id for grader
        double m_grade; //number grades, not letter grades
        string m_grader_comment = ""; //grader comment on submission
        bool m_late; //true if late, fale if not late
        stringstream open_sub, compile_sub, run_sub; //string streams for system commands to display, compile, and run submission files
        string m_grader_username; //determines the path used to get to the submission file
        double m_student_id; //student ID, also used for file path
        string m_file_type; //file type, i.e. cpp, java, python
        string m_file_ext; //file extension

        //example file path: "C:/Users/" << m_grader_username << "/Desktop/git/CPE810C_2016F_Canvas/HW_Automation/submission_file/assignment_" << m_assignment_id << "/" << m_student_id << "/" << m_file_name << "." << m_file_ext << "&";


    public:

        Submission(string file_name, long assignment_id, long course_id, int submission_num, int grader_id, double grade, bool late, string grader_username, double student_id)
            : m_file_name(file_name), m_assignment_id(assignment_id), m_course_id(course_id), m_submission_num(submission_num), m_grader_id(grader_id), m_grade(grade), m_late(late), m_grader_username(grader_username), m_student_id(student_id) {}

        friend ostream& operator <<(ostream& s, Submission sub)
        {
            return s << "Submission #" << sub.m_submission_num << ", File Name: \'" << sub.m_file_name << "\': Assignment " << sub.m_assignment_id << ", Course " << sub.m_course_id << ", Grader ID: " << sub.m_grader_id << ", Grade: " << sub.m_grade << ", Comments: " << sub.m_grader_comment << std::endl;
        }

        //TODO: get download method from other group
        //downloads the submitted file from canvas based on course ID, assignment ID, and student ID
        void download() {}

        //checks the file type of the submssion file
        //sets m_file_ext and m_file_type variables
        void check_file_type()
        {
            stringstream ss1; //used to get filename without the extension
            int index = 0; //index of period in file name
            //iterator up until the period
            for (unsigned int i = 0; i < m_file_name.size(); i++)
            {
                if (m_file_name[i] == '.')
                {
                    index = i;
                    break;
                }
                ss1 << m_file_name[i];
            }

            stringstream ss2; //used to get the filename extension and from that, to determine the file type
            for (unsigned int i = index + 1; i < m_file_name.size(); i++)
            {
                ss2 << m_file_name[i];
            }
            if (ss2.str() == "py") //python
            {
                m_file_type = "python";
            }
            else if (ss2.str() == "java") //java
            {
                m_file_type = "java";
            }
            else if (ss2.str() == "cpp" || ss2.str() == "cc" || ss2.str() == "hh" || ss2.str() == "h") //c++
            {
                m_file_type = "c++";
            }
            else
            {
                //error message?
                //cout << "Not a valid file type. File: " << m_file_name << endl;
                m_file_type = "Error: Bad File Name";
            }
            m_file_ext = ss2.str(); //set file extension
            m_file_name = ss1.str(); //set file name without file extension
            //cout << "Ext: " << m_file_ext << endl;
            cout << "File Type: " << m_file_type << endl; //prints out the recognized file type
        }

        //opens and displays file/source code from the submissions object
        void display_source_code()
        {
            //open submission file, opens in Qt
            if (m_file_type == "Error: Bad File Name")
            {
                cout << "Could not open the file - bad file name." << endl;
            }
            else
            {
                //open_sub << "C:/Users/" << m_grader_username << "/Desktop/git/CPE810C_2016F_Canvas/HW_Automation/submission_file/assignment_" << m_assignment_id
                //         << "/" << m_student_id << "/" << m_file_name << "." << m_file_ext << "&";
                open_sub << "start "" ../HW_Automation/submission_file/assignment_"
                         << m_assignment_id << "/" << m_student_id << "/" << m_file_name << "." << m_file_ext;
                system(open_sub.str().c_str());
            }
        }

        //compiles a submitted file
        bool compile_submission()
        {
            //check for file type and run corresponding command

            if (m_file_type == "c++")
            {
                //compile_sub << "g++ -std=c++11 C:/Users/" << m_grader_username << "/Desktop/git/CPE810C_2016F_Canvas/HW_Automation/submission_file/assignment_"
                //            << m_assignment_id << "/" << m_student_id << "/" << m_file_name << "." << m_file_ext;
                //compile_sub << " -o C:/Users/" << m_grader_username << "/Desktop/git/CPE810C_2016F_Canvas/HW_Automation/submission_file/assignment_"
                //            << m_assignment_id << "/" << m_student_id << "/" << m_file_name;
                compile_sub << "g++ -std=c++11 ../HW_Automation/submission_file/assignment_"
                            << m_assignment_id << "/" << m_student_id << "/" << m_file_name << "." << m_file_ext;
                compile_sub << " -o ../HW_Automation/submission_file/assignment_"
                            << m_assignment_id << "/" << m_student_id << "/" << m_file_name;
            }

            else if (m_file_type == "java")
            {
                compile_sub << "javac ../HW_Automation/submission_file/assignment_"
                            << m_assignment_id << "/" << m_student_id << "/" << m_file_name << "." << m_file_ext;
                //cout << compile_sub.str() << endl;
            }

            else if (m_file_type == "python")
            {
                cout << "Python file: cannot compile" << endl;
            }

            system(compile_sub.str().c_str());
            return true;
        }

        //runs a submitted file
        bool run_submission()
        {
            //check for file type and run corresponding command

            if (m_file_type == "c++")
            {
                cout << "\nOutput:" << endl;
                //run_sub << "./../HW_Automation/submission_file/assignment_"
                //        << m_assignment_id << "/" << m_student_id << "/" << m_file_name;
                run_sub << "ls /.";
            }

            else if (m_file_type == "java")
            {
                //cout << "RUN" << endl;
                cout << "\nOutput:" << endl;
                run_sub << "java -cp /../HW_Automation/submission_file/assignment_"
                        << m_assignment_id << "/" << m_student_id << "/" << m_file_name;
                cout << run_sub.str() << endl;
            }

            else if (m_file_type == "python")
            {
                cout << "Python file: cannot run" << endl;
            }

            //run_sub << "C:/Users/" << m_grader_username << "/Desktop/git/CPE810C_2016F_Canvas/HW_Automation/submission_file/assignment_" << m_assignment_id << "/" << m_student_id << "/Test.exe&";
            system(run_sub.str().c_str());
            return true;
        }

        //grades a submitted file, grade provided by grader (user)
        double grade()
        {
            check_file_type(); //checkes file type and sets m_file_type to python, java, or c++ and m_file_name to the file name without the extension
            //display the source code
            display_source_code();
            //initially set grade to 0
            double grade = 0;
            //compile the submission
            bool compiled = compile_submission();
            if (compiled)
            {
                grade += 75;
                //run submssion
                bool ran = run_submission();
                if (ran)
                {
                    grade += 25;
                }
            }
            //prompt grader to enter grade
            cout << "\nPlease enter grade: ";
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
            //string comment = grade_comment(); //this is called in the course class in the gradeStudents method
            return grade;
        }

        //returns grade entered by the grader, if he chooses to overwrite the default grade
        //not currently used
        double overwrite_grade(double grade)
        {            
            m_grade = grade;
            return grade;
        }

        //returns a comment from the grader to the submission file as a string
        //sets m_grade_comment variable
        string grade_comment()
        {
            cout << "Please enter any submission comments (if none, hit enter): ";
            string comment;
            cin.ignore();
            getline(cin, comment);
            cout << endl;
            m_grader_comment = comment;
            return comment;
        }

        //sets the grader username for file path
        //not currently used
        void setGraderUsername(string name)
        {
            m_grader_username = name;
        }

        //public get methods

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
