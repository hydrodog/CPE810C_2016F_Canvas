//#include <iostream>
//#include <string>
//#include <curl/curl.h>
//#include <fstream>
//using namespace std;
//
//#ifdef _debug
//#pragma comment(lib, "/libcurl_a_debug.lib")
//#else
//#pragma comment(lib, "/libcurl_a.lib")
//#endif
//int main()
//{
//	FILE *bodyfile;	
//
//	bodyfile = fopen("myfile.json", "w");
//	CURL *hnd = curl_easy_init();
//
//	curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "PUT");
//	curl_easy_setopt(hnd, CURLOPT_URL, "https://sit.instructure.com/api/v1/courses/133/assignments/46024/submissions/19850");
//	struct curl_slist *headers = NULL;
//	headers = curl_slist_append(headers, "authorization: Bearer 1030~4MvxMX4ZFH8LCUAe9pFKhNUwFc6o4PnsFny5vlO4sLdyExxx3B9SR3ULM2nzl211");
//	headers = curl_slist_append(headers, "accept: application/json");
//	headers = curl_slist_append(headers, "content-type: application/json");
//	curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, "{\"comment\":{\"text_comment\" : \"asdfasdgasdfasdfasdf\"},\"submission\":{\"posted_grade\": \"22\"} }");
//	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);
//	curl_easy_setopt(hnd, CURLOPT_WRITEDATA, bodyfile);
//
//	CURLcode ret = curl_easy_perform(hnd);
//	fclose(bodyfile);
//	return 0;
//}



#include "Canvas_Update.h"

int main()
{
	Canvas_Update update("test", 133 , 46024 , "1030~4MvxMX4ZFH8LCUAe9pFKhNUwFc6o4PnsFny5vlO4sLdyExxx3B9SR3ULM2nzl211");

}

