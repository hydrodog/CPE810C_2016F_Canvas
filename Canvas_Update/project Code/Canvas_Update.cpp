#include "Canvas_Update.h"
#include <fstream>



Canvas_Update::Canvas_Update(char * greads_file_dir, int courseId, int AssignmentsId, string auth)
{
	greads_file_dir = greads_file_dir;
	courseId = courseId;	
	AssignmentsId = AssignmentsId;
	auth = "authorization: Bearer " + auth;
	update_Api = "https://sit.instructure.com/api/v1/course/" + to_string(courseId) + "/assignments/" + to_string(AssignmentsId) + "/submissions/";
	getGradeInfo(greads_file_dir);
	convertData(gradeList);
	sendRequest();

}

void Canvas_Update::getGradeInfo(char * greads_file_dir)
{
	//FILE *gradefile;
	//read the file and get the data into gradelist
	//here is for test
	grade_info stu1;
	stu1.Stu_ID = "19850";
	stu1.group_comment = false;
	stu1.posted_grade = "11";
	stu1.text_comment = "dont worry, it is just a test";
	gradeList.push_back(stu1);

}

void Canvas_Update::convertData(vector<grade_info> gradeList)
{
	for (int i = 0; i < gradeList.size(); i++)
	{
		reqBody[i] = "{\"comment\":{\"text_comment\" : \"" + gradeList[i].text_comment + "\"},\"submission\":{\"" + gradeList[i].posted_grade + "\"} }";
		stuIdList[i] = gradeList[i].Stu_ID;
	}

}

void Canvas_Update::sendRequest()
{
	for (int i = 0; i < gradeList.size(); i++)
	{
		    string puturl = update_Api + stuIdList[i];
			CURL *hnd = curl_easy_init();
			curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "PUT");
			curl_easy_setopt(hnd, CURLOPT_URL, puturl);
			struct curl_slist *headers = NULL;
			headers = curl_slist_append(headers, auth);
			headers = curl_slist_append(headers, "accept: application/json");
			headers = curl_slist_append(headers, "content-type: application/json");
			curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, reqBody[i]);
			curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);
			CURLcode ret = curl_easy_perform(hnd);
	}
	
}
