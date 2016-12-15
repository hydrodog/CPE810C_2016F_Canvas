#include <iostream>
#include "hw_automation.hh"
#include "../Curving/curving.h"

using namespace std;


//class hw_automation
//{
    /*
    private:
        Course course;

    public:
        hw_automation(string course_name, long course_id, string course_code, long account_id, long student_id)
            : course(course_id, course_name, course_code, account_id, student_id) {}

        //returns course object
        Course getCourse()
        {
            //GET /api/v1/courses/:id
            return course;
        }
        */
//};

int main()
{
    string course_name = "C++";
    long course_id = 123;
    string course_code = "EE810";
    long account_id = 234; //account associated with the course, maybe for the professor?

    //doesn't yet affect anything in the program
    //will eventually modify code based on whether os is "windows" or "mac"
    while (1)
    {
        cout << "Are you using windows or mac? ";
        string os; //operating system
        cin >> os;
        if (os == "mac" || os == "windows")
        {
            break;
        }
        else
        {
            cout << "Error: Please enter \'windows\' or \'mac\'.\n";
        }
    }


    cout << "What is your computer's username? ";
    string grader_username;
    //assume input is a string and is correct, for now
    cin >> grader_username;
    cout << "\n\n";

    hw_automation hwa(course_name, course_id, course_code, account_id);

    cout << "Course: " << hwa.getCourse().getCourseName() << " " << hwa.getCourse().getCourseID() << " " << hwa.getCourse().getCourseCode() << " " << hwa.getCourse().getAccountID() << endl;
    Course c = hwa.getCourse();
    //c.addAssignmentToStudents();

    c.gradeStudents(grader_username);
    cout << endl;
    c.showStudentGradesAndComments();

    Curving curve(vector<double> data);
    //vector<Assignment> assignment_vect = c.getAssignments(); //print out all assignments
    //c.getStudents(); //outputs nothing as of now
    //c.getAssignmentsFromStudent(); //prints out students and assignment informtion from the student object
    //cout << "\n\n" << assignment_vect[0] << endl;
    //Submission s = assignment_vect[0].getSubmission(grader_username); //wrong submission constructor
    //s.display_source_code();
    //s.compile_submission();
    //s.run_submission();
    //s.grade(); //calls compile and run on the submssion
    //cout << "\n" << assignment_vect[0] << endl; //doesn't change assignment grade yet - only the grade variable in the submission class

    return 0;
}

