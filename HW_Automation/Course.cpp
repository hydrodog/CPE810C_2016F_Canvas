#include <iostream>
#include <string>
#include <vector>
#include "Assignment.cpp"
using namespace std;

class Course
{
    private:
        long m_course_id;
        string m_course_name;
        string m_course_code;
        long m_account_id;
        long m_student_id;
        //string m_student_name;

    public:
        Course(int course_id, string course_name, string course_code, long account_id, long student_id) :
            m_course_id(course_id), m_course_name(course_name), m_course_code(course_code), m_account_id(account_id), m_student_id(student_id) {}

        //may need to change return type
        vector<Assignment>  getAssignments()
        {
            //List assignments
            //GET /api/v1/courses/:course_id/assignments
            //store each assignment as an element in a vector

            //fake vector of assignments for now
            vector<Assignment> assignment_vect;
            Assignment assignment(50, 125, 10311, 0);
            assignment_vect.push_back(assignment);
            return assignment_vect;

            //for loop to iterate through assignments
        }
};
