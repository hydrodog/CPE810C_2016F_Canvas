#include <iostream>
#include <fstream>
using namespace std;

class Submission
{
    private:
        long m_assignment_id;
        //Assignment m_assignment;
        long m_course_id;
        //Course m_course;
        int m_submission_num; //submission attempt number
        long m_student_id;
        int m_grader_id;
        double m_grade; //number grades, not letter grades
        string m_grader_comment = "";
        bool m_late;
        //bool excused; //if not completed, it doesn't affect the grade

    public:

        Submission(long assignment_id, long course_id, int submission_num, long student_id, int grader_id, double grade, bool late)
            : m_assignment_id(assignment_id), m_course_id(course_id), m_submission_num(submission_num), m_student_id(student_id), m_grader_id(grader_id), m_grade(grade), m_late(late) {}

        //TODO: get public methods from upload and download team so that we can download a submission and then upload a grade

        //TODO: get download method from other group
        //downloads the submitted file from a submissions object
        void download() {}

        //TODO
        //compiles a submitted file, return true if compiles, return false if not compiled
        bool compile_submission()
        {
            return true;
        }

        //TODO
        //runs a submitted file, returns true if run, returns false, if not run
        bool run_submission()
        {
            return true;
        }

        //grades a submitted file, giving 50 points is it compiles and another 50 points if it runs. If neither, it gives a score of 25.
        double grade()
        {
            double grade = 0;
            bool compiled = compile_submission();
            if (compiled)
            {
                grade += 75;
                bool ran = run_submission();
                if (ran)
                {
                    grade += 25;
                }
            }

            m_grade = grade;
            return grade;
        }

        //TODO: once download is figured out
        //opens and displays file/source code from the submissions object
        void display_source_code() {}

        //returns grade entered by the grader, if he chooses to overwrite the default grade
        double overwrite_grade(double grade)
        {
            m_grade = grade;
            return grade;
        }

        //adds a comment from the grader to the submission file
        string grade_comment(string comment)
        {
            m_grader_comment = comment;
            return comment;
        }

        //TODO: Get function from plagiarism detector group
        //returns a similarity score between the submitted file and other files
        double plag_detector()
        {
            return 0;
        }

        //TODO: Get upload function from upload group
        //uploads a grade and possibly a comment to the submission object
        void upload() {}
};
