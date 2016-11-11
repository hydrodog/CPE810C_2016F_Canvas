#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Course
{
    private:
        long m_course_id;
        string m_course_name;
        string m_course_code;
        long m_account_id;
        long m_student_user_id;
        //string m_student_name;

    public:
        Course(int course_id, string course_name, string course_code, long account_id, string student_user_id) : m_course_id(course_id), m_course_name(course_name), m_course_code(course_code), m_account_id(account_ide), m_student_user_id(student_user_id) {}

        //may need to change return type
        vector<Assignment>  getAssignments()
        {
            //List assignments
            //GET /api/v1/courses/:course_id/assignments
            //store each assignment as an element in a vector
            return NULL;
        }
};

int main(int argc, char *argv[])
{


    return 0;
}
