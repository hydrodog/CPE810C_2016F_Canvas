#include <CanvasUpdate.h>
#include <iostream>
#include <string>
#include "curl_easy.h"
#include "curl_form.h"
#include "curl_header.h"

using namespace curl;
using namespace std;

#ifdef _DEBUG
#pragma comment(lib, "/libcurl_a_debug.lib")
#else
#pragma comment(lib, "/libcurl_a.lib")
#endif

using curl::curl_easy;
using curl::curl_easy_exception;


Canvas_Update::Canvas_Update(char *greads_file_dir,int courseId,int AssignmentsId, string auth,int Post_size))
{
	greads_file_dir = greads_file_dir;
	courseId = courseId;
	AssignmentsId = AssignmentsId;
	auth = auth;
	Post_size = Post_size;
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
	string PostData="";
	PostData += string(oneGrade.text_comment);
	PostData += string(oneGrade.group_comment);
	PostData += string(oneGrade.visibility);
	PostData += string(oneGrade.posted_grade);
	PostData += string(oneGrade.excuse);
	return PostData;

}

Canvas_Update::writeRequest(grade_info *gradeList,int Post_size)
{
	for (int i = 0; i < Post_size; ++i)
	{
	    curl_easy easy;
            curl_header header;
            curl_form form;
            // Add some options.
            string PostData = convertData(gradeList[i]);
            string auth = "Authorization: Bearer" + auth;
            header.add(auth);
            easy.add<CURLOPT_URL>(update_Api);
            easy.add<CURLOPT_FOLLOWLOCATION>(1L);
            try {
                    // Execute the request.
                    header.add("Content-type: application/json");
                    header.add("Accept: application/json");
                    easy.add<CURLOPT_CUSTOMREQUEST>("POST");
                    easy.add<CURLOPT_HTTPHEADER>(header.get());
                    easy.add<CURLOPT_POSTFIELDS>(PostData);
                    easy.add<CURLOPT_FOLLOWLOCATION>(1L);
            }
            catch (curl_easy_exception error) {
                    // If you want to get the entire error stack we can do:
                    auto errors = error.what();
                    // Otherwise we could print the stack like this:
                    error.print_traceback();
                    // Note that the printing the stack will erase it
            }
	}



}



