This repository is for the update part of EE810 Canvas group

In update section,
we use libcurl lib https://curl.haxx.se/ and JosephP91/curlcpp lib https://github.com/JosephP91/curlcpp 
This two libs is used to connect with Canvas API, and we use the api to update the data to Canvas.

Here is the header file of our project

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
            int Stu_ID;
                string text_comment; //add a textual comment to the submission.
                bool   group_comment;//whether or not this comment should be sent to the entire group(defaults to false).ignored if this is not a group assignment or if no text_comment is provided.
                //string media_comment_id//add an audio/video comment to the submission. media comments can be added via this api
                //string media_comment_type//type of media comment being added.allow audio, video
                //int	   comment_file_ids//Attach files to this comment that were previously uploaded using the Submission Comment API's files action
                string visibility//Whether this assignment is visible to the owner of the submission
                string posted_grade//the grade of the submission
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
                int Stu_ID[100];
                static string auth;//the taken access of Canvas
                string update_Api;
                int Post_size;
        public:
                Canvas_Update(char *greads_file_dir,int courseId,int AssignmentsId, string auth,int Post_size);//construction function
                void getGradeInfo(*greads_file_dir);//convert the grades data into json 
                void writeRequest(grade_info *gradeList,int Post_size);//write the request
                bool sendRequest(string auth, string update_Api);//send the request to Canvas
        };




The libcurl use in project 

        //this is a function to post the assignment on Canvas, and we are going to make a similar package above this function
        //but we still meet some problem in this function
        #include <iostream>
        #include <string>
        #include "curl_easy.h"
        #include "curl_form.h"
        #include "curl_header.h"

        using namespace curl;
        using namespace std;

        /*
        * This example shows how to make a simple request with
        * curl.
        */
        #ifdef _DEBUG
        #pragma comment(lib, "/libcurl_a_debug.lib")
        #else
        #pragma comment(lib, "/libcurl_a.lib")
        #endif

        using curl::curl_easy;
        using curl::curl_easy_exception;


        int main() {
                // Easy object to handle the connection.
                curl_easy easy;
                curl_header header;
                curl_form form;
                // Add some options.
                const char* auth = "Authorization: Bearer xxxxxxx";
                header.add(auth);
                easy.add<CURLOPT_URL>(" Your API URL");
                easy.add<CURLOPT_FOLLOWLOCATION>(1L);
                try {
                        // Execute the request.
                        header.add("Content-type: application/json");
                        header.add("Accept: application/json");
                        easy.add<CURLOPT_CUSTOMREQUEST>("POST");
                        easy.add<CURLOPT_HTTPHEADER>(header.get());
                        easy.add<CURLOPT_POSTFIELDS>("\"id\":12346,{ \"name\":\"TTTTTTTT\",\"submission_types\":\"online_text_entry\"}");
                        easy.add<CURLOPT_FOLLOWLOCATION>(1L);
                        easy.perform();
                }
                catch (curl_easy_exception error) {
                        // If you want to get the entire error stack we can do:
                        auto errors = error.what();
                        // Otherwise we could print the stack like this:
                        error.print_traceback();
                        // Note that the printing the stack will erase it
                }
                system("pause");
                return 0;
        }
