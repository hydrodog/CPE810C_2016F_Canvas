Hi team member's, I spend a lot of time on the question about how to use the API to operate the data in Canvas. The following is the experience I make for you.

If you use GET or DELETE operation to get the information or delete the date on the Canvas, you don't need to write the request parameters in the request body. Because the only data needed will be writen in the header and the URL.

But if you want to use the PUT or POST request, you have to write the request body which could let the Canvas know which data you want to make a update.

We are the upadate group which require us to update the grades of the submission to the Canvas. The following is the Grade or comment on a submission API.

https://canvas.instructure.com/doc/api/submissions.html#method.submissions_api.update

In this API, you could find the data info we could update.

The only thing I want to tell you is that the format of request in Json.
In the doc we could find the following data.

	Parameter		              Type	         Description
	comment[text_comment]		  string         Add a textual comment to the submission.
	comment[group_comment]	      boolean	     Whether or not this comment should be sent to the entire group (defaults to false). 
	submission[posted_grade]	  string	     Assign a score to the submission, updating both the “score” and “grade” fields on the submission record.

So how to write the request body(not the header) in Json   ******It is not clear signed in the API doc******
here is the example. 

	{
		"comment":{
			"text_comment":"sick API, I can get it now"
		},
		"submission":{
			"posted_grade": "99"
		}
	}

you could find there need a top level such like the comment. Just a some details, if you find it, you will know everything.
The next work is to convert the function into c++ class, come on!

further more, If we want to Grade or comment on multiple submissions. Use the following API:
POST /api/v1/courses/:course_id/assignments/:assignment_id/submissions/update_grades
The example:
	{
		"grade_data":{
			"7672":{"posted_grade" :"0","text_comment" :"I am Superman!"},
			"20285":{"posted_grade" :"0","text_comment" :"You are bad"}
			}
	}

