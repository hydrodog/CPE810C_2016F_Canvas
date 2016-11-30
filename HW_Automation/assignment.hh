#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <iostream>
#include "Submission.hh"
using namespace std;

//class Submission;

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
            return Submission("test.cpp", m_assignment_id, m_course_id, 1, 323, 0.0, false);
        }

        friend ostream& operator <<(ostream& s, Assignment a)
        {
                return s << "Assignment " << a.m_assignment_id << ", Course " << a.m_course_id << ", Grade: " << a.m_grade << std::endl;
        }

        long get_assignment_id()
        {
            return m_assignment_id;
        }
        long get_course_id()
        {
            return m_course_id;
        }
        double getGrade()
        {
            return m_grade;
        }
};

#endif // ASSIGNMENT_HH
