#ifndef CanvasUpdate_H
#define CanvasUpdate_H
#include <stdio.h>
#include <string>
#include <curl/curl.h>
#include <Canvas_Homework_Automation.h>

static string updateAPI= "https://sit.instructure.com/api/v1/";

//There are two APIs to update the grade
//1.Grade or comment on a submission
//2.Grade or comment on multiple submissions
//we choose the first way upate the submission one by one

static bool UpdateState;// the state of the uodate processing, true means the processing is successful, flase means flase
	
//////////////////////// the struct of gradeInfo to post; 
struct grade_info //define the single submission grades struct
{
    int Student_ID;
        string Assignment_Comment; //add a textual comment to the submission.
	bool   group_comment;//whether or not this comment should be sent to the entire group(defaults to false).ignored if this is not a group assignment or if no text_comment is provided.
	//string media_comment_id//add an audio/video comment to the submission. media comments can be added via this api
	//string media_comment_type//type of media comment being added.allow audio, video
	//int	   comment_file_ids//Attach files to this comment that were previously uploaded using the Submission Comment API's files action
	string visibility;//Whether this assignment is visible to the owner of the submission
	string posted_grade;//the grade of the submission
	bool   excuse;//Sets the “excused” status of an assignment.
};

///////////////////////// Update class

class Canvas_Update
{
private:
	char *greads_file_dir;//the grades file path, the Homework Automation group should provide
	grade_info *gradeList;
	int courseId;
	int AssignmentsId;
        int Student_ID[100];
	static string auth;//the taken access of Canvas
	string update_Api;
	int Post_size;
public:
	Canvas_Update(char *greads_file_dir,int courseId,int AssignmentsId, string auth,int Post_size);//construction function
	string convertData(grade_info oneGrade);
	void getGradeInfo(*greads_file_dir);//convert the grades data into json 
	void writeRequest(grade_info *gradeList,int Post_size);//write the request
};

#endif
