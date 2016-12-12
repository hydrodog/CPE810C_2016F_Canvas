#ifndef CanvasUpdate_H
#define CanvasUpdate_H
#include <stdio.h>
#include <string>
#include <curl/curl.h>
#include <vector>
using namespace std;

#ifdef _debug
#pragma comment(lib, "/libcurl_a_debug.lib")
#else
#pragma comment(lib, "/libcurl_a.lib")
#endif

//string APIheader = "https://sit.instructure.com/api/v1/";

//There are two APIs to update the grade
//1.Grade or comment on a submission
//2.Grade or comment on multiple submissions
//we choose the first way upate the submission one by one
//bool UpdateState;// the state of the uodate processing, true means the processing is successful, flase means flase

// the struct of gradeInfo to post; 


struct grade_info //define the single submission grades struct

{
	string Stu_ID;
	string text_comment; //add a textual comment to the submission.
	bool   group_comment;//whether or not this comment should be sent to the entire group(defaults to false).ignored if this is not a group assignment or if no text_comment is provided.
	string posted_grade;//the grade of the submission
						//string media_comment_id//add an audio/video comment to the submission. media comments can be added via this api
						//string media_comment_type//type of media comment being added.allow audio, video
					    //int      comment_file_ids//Attach files to this comment that were previously uploaded using the Submission Comment API's files action
						//string visibility//Whether this assignment is visible to the owner of the submission
						//bool   excuse;//Sets the “excused” status of an assignment.
};



// Update class



class Canvas_Update

{

private:

	char *greads_file_dir;//the grades file path, the Homework Automation group should provide
	vector<grade_info> gradeList;
	vector<string> stuIdList;
	vector<string> reqBody;
	int courseId;
	int AssignmentsId;
	const char *auth;//the taken access of Canvas
	string update_Api;

public:
	Canvas_Update(char *greads_file_dir, int courseId, int AssignmentsId, string auth);//construction function
	void getGradeInfo(char *greads_file_dir);
	void convertData(vector<grade_info> gradeList);	//convert the grades data into string type
	void sendRequest();//send the request to Canvas
};

#endif
