#ifndef HW_AUTOMATION_H
#define HW_AUTOMATION_H

#include <iostream>
#include "Course.hh"
using namespace std;

//class Course;

class hw_automation
{
    private:
        //course that the assignments that are to be graded fall under
        Course course;

    public:
        //Constructor, builds course object
        hw_automation(string course_name, long course_id, string course_code, long account_id)
            : course(course_id, course_name, course_code, account_id) {}

    //returns course object
    Course getCourse()
    {
        //GET /api/v1/courses/:id
        return course;
    }
};

#endif // HW_AUTOMATION_HH
