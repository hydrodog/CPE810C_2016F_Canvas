#include <iostream>
#include "hw_automation.hh"
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
    long account_id = 234;

    hw_automation hwa(course_name, course_id,course_code,account_id);

    cout << "Course: " << hwa.getCourse().getCourseName() << " " << hwa.getCourse().getCourseID() << " " << hwa.getCourse().getCourseCode() << " " << hwa.getCourse().getAccountID() << endl;
    Course c = hwa.getCourse();
    vector<Assignment> assignment_vect = c.getAssignments(); //print out all assignments
    c.getStudents(); //outputs nothing as of now
    c.getAssignmentsFromStudent(); //prints out students and assignment informtion from the student object
    cout << "\n\n" << assignment_vect[0] << endl;
    Submission s = assignment_vect[0].getSubmission();
    s.display_source_code();
    s.compile_submission();
    s.run_submission();

    return 0;
}

