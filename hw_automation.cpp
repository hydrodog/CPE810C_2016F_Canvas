#include <iostream>
#include "Course.cpp"
using namespace std;

class hw_automation
{
    private:
        Course course;

    public:
        hw_automation(string course_name, string course_code, long account_id, long student_user_id)
            : course(course_name, course_code, account_id, student_user_id) {}

        //returns course object
        Course getCourse()
        {
            //GET /api/v1/courses/:id
            return course;
        }
};

int main(int argc, char *argv[])
{
    return 0;
}
