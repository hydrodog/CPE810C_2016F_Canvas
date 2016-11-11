README
HW_AUTOMATION

Class hw_automation : Encompasses all of the HW automation tasks.

	Private Data Members:
	
	Course course
	• A course object on which the hw_automation tasks will be performed

	Methods:

	hw_automation (string course_name, string course_code, long account_id, long student_user_id)
	• Constructor, constructs a hw_automation object as well as a course object
	Course getCourse () {}
	• Returns the course object, containing all the necessary information about the course

Class Course : Represents a course/class in canvas.

	Private Data Members:

	long m_course_id
	• identifiaction number of the course
        string m_course_name
	• name of the course
        string m_course_code
	• code of the course
        long m_account_id
	• identification number for the account associated with the course
        long m_student_id
	• user identification number for a given student

	Methods:

	Course(int course_id, string course_name, string course_code, long account_id, string student_user_id)
	• Contructor, constructs a course object given certain information
	
	vector<Assignment>  getAssignments()
	• Returns a vector of all the assignments for a given course
          
Class Assignment:

	Private Data Members:
	
	long m_assignment_id
	• identification number of the assignment
        long m_course_id;
	• identification number of the course
        long m_student_id;
	• user identification number for a given student
        double m_grade;
	• grade for a given assignment

	Methods:
	
	Assignment(long assignment_id, long course_id, long studnet_id, double grade)
	• Constructor, constructs an assignment object given certain information
	
	Submission getSubmissions () {}
	• Returns the submission for a given student for the corresponding assignment

Class Submission:

	Private Data Members:

	long m_assignment_id
	• identification number of the submission's corresponding assignment
        long m_course_id
	• identification number of the submission's/assignment's course
        int m_submission_num
	• the number of times the student has made a submission / number of attempts at a submission
        long m_student_id;
	• user identification number for a given student
        int m_grader_id;
	• identification number for the grader
        double m_grade
	• grade for the assignment, determined by submission object. number grades, not letter grades
        string m_grader_comment
	• grader comments, initialized as an empty string
        bool m_late;
	• a flag for if an assignment is late

	Methods:
	
	Submission(long assignment_id, long course_id, int submission_num = 0, long student_id, int grader_id, double grade, bool late = false)
	• Constructor, constructs a submission object given certain information

	void download () {}
	• Downloads a submission's file

	bool compile submission () {}
	• Compiles the submitted file and return true if it compiles, false if it doesn't

	bool run_submissions () {}
	• Runs the submitted file and returns true if it runs, false if it doesn't

	double grade (bool compiled, bool ran) {}
	• Returns the grade of the assignment
	• Gives a 50% if the submitted file compiles and another 50% if it runs
	• Gives default score of 25% if the submitted file neither compiled nor ran

	void display_source_code() {}
	• Opens and displays the submitted file or source code to the grader 

	double_overwrite_grade(double grade) {}
	• Returns the grade that the grader wants to give the assignment
	• Overwrites default grading

	string grade_comment(string comment) {}
	• Adds a comment from grader to the submission object

	double plag_detector()
	• Detects the plagiarism of the submitted assignment by returning a similarity score between the submitted file and other files

	void upload () {}
	• This function uploads the comment along with grades to the submission object



