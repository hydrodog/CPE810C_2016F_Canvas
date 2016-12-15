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
        Assignment(long assignment_id = 0, long course_id = 0, double grade = 0) : m_assignment_id(assignment_id), m_course_id(course_id), m_grade(grade) {}

        //gets one submission (assume student only submits one thing) for a given student, based on student id and grader id
        //run for each student
        //maybe just get the file for each student
        Submission getSubmission(string filename, string grader_username, double student_id)
        {
            //GET /api/v1/courses/:course_id/assignments/:assignment_id/submissions/:user_id

            //fake submission for now
            return Submission(filename, m_assignment_id, m_course_id, 1, 323, 0.0, false, grader_username, student_id);
        }

        friend ostream& operator <<(ostream& s, Assignment a)
        {
                return s << "Assignment " << a.m_assignment_id << ", Course " << a.m_course_id << ", Grade: " << a.m_grade << std::endl;
        }

        Assignment& operator =(const Assignment & b)
        {
            this->m_assignment_id = b.m_assignment_id;
            this->m_course_id = b.m_course_id;
            this->m_grade = b.m_grade;
            return *this;
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
