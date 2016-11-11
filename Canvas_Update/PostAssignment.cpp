//this is a function to post the assignment on Canvas, and we are going to make a package above this function
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
