//upload the grade of assignment on Canvas
#include <iostream>
#include <string>
#include "curl_easy.h"
#include "curl_form.h"
#include "curl_header.h"

using namespace curl;
using namespace std;



/*
   To post grade to canvas
   we should know the CourseId,AssignmentId,UseId,Grade and Token.

 */


class UpdateGrade{
    private:
         String courseId;
         String AssignmentId;
         String userId;
         String token;
         static String targetURL;
         double grade;
    public:
        UpdateGrade(String courseId, String AssignmentId, String userId,String token,double grade):courseId(courseId),AssignmentId(AssignmentId),
        userId(userId),token(token),grade(grade){
             UpdateGrade.targetURL = "https://canvas.instructure.com/api/v1"
                + "/courses/"+courseId
                + "/assignments/"+AssignmentId
                + "/submissions/update_grades"
                + "?access_token="
                + token
                + "&grade_data["+userId+"[posted_grade]="+grade;
        }

        void post(){
            try {

                    URL targetUrl = new URL(targetURL);

                    HttpURLConnection httpConnection = (HttpURLConnection) targetUrl.openConnection();
                    httpConnection.setDoOutput(true);
                    httpConnection.setRequestMethod("POST");
                    httpConnection.setRequestProperty("Content-Type", "application/json");

                    if (httpConnection.getResponseCode() != 200) {
                        throw new RuntimeException("Failed : HTTP error code : "
                            + httpConnection.getResponseCode());
                    }

                    BufferedReader responseBuffer = new BufferedReader(new InputStreamReader(
                            (httpConnection.getInputStream())));

                    String output;
                    System.out.println("Output from Server:\n");
                    while ((output = responseBuffer.readLine()) != null) {
                        System.out.println(output);
                    }

                    httpConnection.disconnect();
                    //return "success!";

                  } catch (MalformedURLException e) {

                    e.printStackTrace();

                  } catch (IOException e) {

                    e.printStackTrace();

                 }

                }
        void printurl(){
              return targetURL;
        }

    }


