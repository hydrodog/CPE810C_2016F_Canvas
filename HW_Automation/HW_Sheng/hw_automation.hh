#ifndef HW_AUTOMATION_HH
#define HW_AUTOMATION_HH

#include <iostream>
//#include "Course.hh"
using namespace std;

class Course;

class hw_automation
{
    private:
        Course course;

    public:
        hw_automation(string course_name, long course_id, string course_code, long account_id)
            : course(course_id, course_name, course_code, account_id) {}

        //returns course object
        Course getCourse()
        {
            //GET /api/v1/courses/:id
            return course;
        }

    int main()
    {
        return 0;
    }
};

#endif // HW_AUTOMATION_HH
