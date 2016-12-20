README
HW_AUTOMATION

Class Assignment_Unzip : This class is used for its student struct

Class hw_automation : Encompasses all of the HW automation tasks.

	Private Data Members:
	
	Course course
	• A course object on which the hw_automation tasks will be performed

	Methods:

	hw_automation (string course_name, long course_id, string course_code, long account_id)
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

        Student *stu = new student [25]
        • pointer to an array of student objects representing students in the course

	Methods:

	Course(int course_id, string course_name, string course_code, long account_id)
	• Contructor, constructs a course object given certain information

        vpod getStudents()
        • Gets the the students in the course and sets each student's identification number, name, and e-mail address

        void getFileInfo(Submission s, Student &stu)
        • Fills in file information within each student object

	void getAssignments()
	• Gets all of the the assignments for a given course

	void chooseAssignment()
	• User chooses assignment
	• Puts the Assignment information in each student object
	• Sets the information of assignment and submission in each student object

	void gradeStudents(string grader_username)
	• Initiates grading operations for each student
	• grader_usernmae is used for the file path
	• Calls plagiarism detector
	• Calls curving function
	• Uploads to canvas 

          
Class Assignment:

	Private Data Members:
	
	long m_assignment_id
	• identification number of the assignment
        long m_course_id;
	• identification number of the course
        double m_grade;
	• grade for a given assignment

	Methods:
	
	Assignment(long assignment_id, long course_id, double grade)
	• Constructor, constructs an assignment object given certain information
	
	Submission getSubmission(string filename, string grader_username, double student_id) 
	• Returns the submission for a given student for the corresponding assignment
	• grade_username is used for the file path
        
	friend ostream& operator <<(ostream& s, Assignment a)
	• Used for outputting assignment objects

	Assignment& operator =(const Assignment & b)
	• sets one assignment equal to another

        long get_assignment_id()
        • Returns the identification number of assignment

        long get_course_id()
        • Returns the identification number of the course
      
        double getGrade()
        • Returns the Grade of student


Class Submission:

	Private Data Members:

        string m_file_name
        • Name of the file of the submission's corresponding assignment
        long m_assignment_id
	• identification number of the submission's corresponding assignment
        long m_course_id
	• identification number of the submission's/assignment's course
        int m_submission_num
	• the number of times the student has made a submission / number of attempts at a submission
        int m_grader_id;
	• identification number for the grader
        double m_grade
	• grade for the assignment, determined by submission object. number grades, not letter grades
        string m_grader_comment
	• grader comments, initialized as an empty string
        bool m_late;
	• a flag for if an assignment is late
	stringstream open_sub
	• string stream used to open the source code of a submission
	stringstream compilen_sub
	• string stream used to compile a submission
	stringstream run_sub
	• string stream used to run a submission
	string m_grader_username
	• grader's computer username
	• used for file path
	double m_student_id
	• student's identification number
	string m_file_type
	• represents the type of sumbission file, i.e. c++ or java
	string m_file_ext
	• file extension of submitted file, i.e. cpp, java

	Methods:
	
	Submission(string file_name,long assignment_id, long course_id, int submission_num = 0, int grader_id, double grade, bool late = false,string grader_username)
	• Constructor, constructs a submission object given certain information

	void download ()
	• Downloads a submission's file

	void check_file_type()
	• checks the type of submission file, i.e. c++, java, or something else

	void display_source_code()
	• displays the source code of the submitted file

	bool compile submission ()
	• Compiles the submitted file based on file type and returns true

	bool run_submissions ()
	• Runs the submitted file based on the file type and returns true

	double grade (bool compiled, bool ran)
	• Returns the grade of the assignment
	• Prompts the user to enter a grade

	double_overwrite_grade(double grade)
	• Returns the grade that the grader wants to give the assignment
	• Overwrites default grading

	string grade_comment(string comment)
	• Adds a comment from grader to the submission object
	• Returns the comment

        void setGraderUsername(string name)
        • Sets the user name to determine the path to get the submitted file

	string getFileName()
	• returns the submission's file name

	long getAssignmentID()
	• returns the submission's corresponding assignment ID

	long getCourseID()
	• returns the submission's corresponding course ID

	int getSubmssionNum()
	• returns the submission number

	int getGraderID()
	• returns the grader ID

	double getGrade()
	• returns the grade of the submission

	string getGraderComment()
	• returns the grader's comment on the submission

	bool getLate()
	• returns whether or not the submission is late



