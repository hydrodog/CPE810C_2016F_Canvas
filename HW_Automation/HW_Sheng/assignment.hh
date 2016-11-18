#ifndef ASSIGNMENT_HH
#define ASSIGNMENT_HH

#include <iostream>
//#include "Submission.hh"
using namespace std;

class Submission;

class Assignment
{
    private:
        long m_assignment_id;
        long m_course_id;
        double m_grade; //need to store grades to get metrics at the end of semester (other groups)

    public:
        Assignment(long assignment_id, long course_id, double grade) : m_assignment_id(assignment_id), m_course_id(course_id), m_grade(grade) {}

        //gets one submission (assume student only submits one thing)
        //run for each student
        //maybe just get the file for each student
        Submission getSubmission()
        {
            //GET /api/v1/courses/:course_id/assignments/:assignment_id/submissions/:user_id

            //fake submission for now
            return Submission(50, 1103, 1, 1564, 541, 0, false);
        }

        long get_assignment_id()
        {
            return m_assignment_id;
        }
        long get_course_id()
        {
            return m_course_id;
        }
};

#endif // ASSIGNMENT_HH