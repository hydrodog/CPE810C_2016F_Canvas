#include <CanvasUpdate.h>

Canvas_Update::Canvas_Update(char *greads_file_dir,int courseId,int AssignmentsId, string auth,int Post_size))
{
	greads_file_dir = greads_file_dir;
	courseId = courseId;
	AssignmentsId = AssignmentsId;
	auth = auth;
	Post_size = Post_size//how many grades we need to update;
	update_Api = API + "course/" + courseId + "/assignments/"+AssignmentsId+"/submissions/";
}

void Canvas_Update::getGradeInfo(*greads_file_dir)
{
	// this part is to get the grades data from the grade file given by Homework Automation group
	// reade the file data and build the list of grade (*gradeList)
	//Here We should know the struct about the file, we need to make a agreement on it
}

string Canvas_Update::convertData(grade_info oneGrade)
{
	//make the request body like this  
	//{\"comment\":{\"text_comment\" : \"asdfasdgasdfasdfasdf\"},\"submission\":{\"posted_grade\": \"99\"} }");
	string commend = "";
	commend += "{\"comment\":{\"text_comment\" : \"" + oneGrade.text_comment + "\"},\"submission\":{\"" + oneGrade.posted_grade + "\"} }";
	return string(commend);
}

Canvas_Update::writeRequest(grade_info *gradeList,int Post_size)
{
	// the following is the example about how to update the grade and comment on sumbmission, and it is work!
	// but there could be anyother API to grade or comment on multiple submissions
	// we could work on it too
	CURL *hnd = curl_easy_init();	
	curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "PUT");
	curl_easy_setopt(hnd, CURLOPT_URL, "https://sit.instructure.com/api/v1/courses/133/assignments/46024/submissions/19850");
	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "authorization: Bearer 1030~4MvxMX4ZFH8LCUAe9pFKhNUwFc6o4PnsFny5vlO4sLdyExxx3B9SR3ULM2nzl211");
	headers = curl_slist_append(headers, "accept: application/json");
	headers = curl_slist_append(headers, "content-type: application/json");
	curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, "{\"comment\":{\"text_comment\" : \"asdfasdgasdfasdfasdf\"},\"submission\":{\"posted_grade\": \"99\"} }");
	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);
	CURLcode ret = curl_easy_perform(hnd);	
}

Canvas_Update::Canvas_Update(char *greads_file_dir,int courseId,int AssignmentsId, string auth,int Post_size))
{
	greads_file_dir = greads_file_dir;
	courseId = courseId;
	AssignmentsId = AssignmentsId;
	auth = auth;
	Post_size = Post_size//how many grades we need to update;
	update_Api = API + "course/" + courseId + "/assignments/"+AssignmentsId+"/submissions/";
}

Canvas_Update::Canvas_Update(char *greads_file_dir,int courseId,int AssignmentsId, string auth,int Post_size))
{
	greads_file_dir = greads_file_dir;
	courseId = courseId;
	AssignmentsId = AssignmentsId;
	auth = auth;
	Post_size = Post_size//how many grades we need to update;
	update_Api = API + "course/" + courseId + "/assignments/"+AssignmentsId+"/submissions/";
}
Canvas_Update::Canvas_Update(char *greads_file_dir,int courseId,int AssignmentsId, string auth,int Post_size))
{
	greads_file_dir = greads_file_dir;
	courseId = courseId;
	AssignmentsId = AssignmentsId;
	auth = auth;
	Post_size = Post_size//how many grades we need to update;
	update_Api = API + "course/" + courseId + "/assignments/"+AssignmentsId+"/submissions/";
}

Canvas_Update::Canvas_Update(char *greads_file_dir,int courseId,int AssignmentsId, string auth,int Post_size))
{
	greads_file_dir = greads_file_dir;
	courseId = courseId;
	AssignmentsId = AssignmentsId;
	auth = auth;
	Post_size = Post_size//how many grades we need to update;
	update_Api = API + "course/" + courseId + "/assignments/"+AssignmentsId+"/submissions/";
}
Canvas_Update::Canvas_Update(char *greads_file_dir,int courseId,int AssignmentsId, string auth,int Post_size))
{
	greads_file_dir = greads_file_dir;
	courseId = courseId;
	AssignmentsId = AssignmentsId;
	auth = auth;
	Post_size = Post_size//how many grades we need to update;
	update_Api = API + "course/" + courseId + "/assignments/"+AssignmentsId+"/submissions/";
}
Canvas_Update::Canvas_Update(char *greads_file_dir,int courseId,int AssignmentsId, string auth,int Post_size))
{
	greads_file_dir = greads_file_dir;
	courseId = courseId;
	AssignmentsId = AssignmentsId;
	auth = auth;
	Post_size = Post_size//how many grades we need to update;
	update_Api = API + "course/" + courseId + "/assignments/"+AssignmentsId+"/submissions/";
}

