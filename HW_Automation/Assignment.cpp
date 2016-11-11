#include <iostream>
#include "Submission.cpp"
using namespace std;

class Assignment
{
    private:
        long m_assignment_id;
        long m_course_id;
        long m_student_id;
        double m_grade;

    public:
        Assignment(long assignment_id, long course_id, long student_id, double grade) : m_assignment_id(assignment_id), m_course_id(course_id), m_student_id(student_id), m_grade(grade) {}

        //gets one submission (assume student only submits one thing)
        Submission getSubmission()
        {
            //GET /api/v1/courses/:course_id/assignments/:assignment_id/submissions/:user_id

            //fake submission for now
            return Submission(50, 1103, 1, 1564, 541, 0, false);
        }
};

