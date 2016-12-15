#include <iostream>
#include "hw_automation.hh"
#include "../Curving/curving.h"

using namespace std;

int main()
{
    //Create a fake course for testing
    string course_name = "C++";
    //long course_id = 123;
    string course_code = "EE810";
    long account_id = 234; //account associated with the course, maybe for the professor?

    //doesn't yet affect anything in the program
    //will eventually modify code based on whether os is "windows" or "mac"
    /*
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
    */

    //Get username for file path on grader's computer
    cout << "What is your computer's username? ";
    string grader_username;
    //assume input is a string and is correct, for now
    cin >> grader_username;
    cout << "\n\n";

    cout << "Please enter the course ID: ";
    long cid;
    cin >> cid;

    cout << endl << endl;

    //create hw automation object
    hw_automation hwa(course_name, cid, course_code, account_id);

    //Display course information from hw automation object
    cout << "Course: " << hwa.getCourse().getCourseName() << " " << hwa.getCourse().getCourseID() << " " << hwa.getCourse().getCourseCode() << " " << hwa.getCourse().getAccountID() << endl;
    //create course object from hw automation object
    Course c = hwa.getCourse();
    //c.addAssignmentToStudents();

    //grade each students assignment submssion
    c.gradeStudents(grader_username);
    cout << endl;

    //display student grades and grade comments for the assignment that was graded
    c.showStudentGradesAndComments();

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

