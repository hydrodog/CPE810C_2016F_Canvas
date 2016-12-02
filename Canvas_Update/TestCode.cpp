// this is a file show the code test the team member made


///////
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



/////////////

//use the Qurl to connect

#include <UpdateGrade_Test.h>

int main(){
  _uploadManager = new QNetworkAccessManager(this);
  connect(_uploadManager,SIGNAL(finished(QNetworkReply*)),SLOT(replyFinished(QNetworkReply*)));
  m_buf = NULL;

  // reading from a json file and writing to a datastream
  QFile file("d:/update.json");
  file.open(QIODevice::ReadOnly);//open the json file in local
  int file_len = file.size();//aquire the size of file
  QDataStream in(&file);//initialize a datastream
  m_buf = new char[file_len];
  in.readRawData( m_buf, file_len);//start to read the json file
  file.close();

  // Make a request
  QNetworkRequest request(QUrl(tr("https://canvas.instructure.com/api/v1/courses/14812/assignments/55596?access_token=1030~cskoY40hPR86qHQM7PdGbjbkoqx93k8AzG3Y0uzEH21FXny2wfAnakD7TzjjnKHR")));
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");
  QByteArray arr = QByteArray(m_buf, file_len);
  _reply = _uploadManager->post(request , arr);
  connect(_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(upLoadError(QNetworkReply::NetworkError)));
  connect(_reply, SIGNAL(uploadProgress ( qint64 ,qint64 )), this, SLOT( OnUploadProgress(qint64 ,qint64 )));
  return 0;
}




////////////// header of the class


#ifndef UpdateGrade_Test_H
#define UpdateGrade_Test_H
#include <QCoreApplication>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <Qssl>
#include <QFile>

/*  This is to test the connection with URL by Qurl because it hard to connect by cURL at present. */

class UpdateGrade_Test{
private:
  QNetworkAccessManager *_uploadManager;
  QNetworkReply *_reply;
  char* m_buf;
private slots:
  void replyFinished( QNetworkReply* );
  void upLoadError(QNetworkReply::NetworkError errorCode);
  void OnUploadProgress( qint64 bytesSent, qint64 bytesTotal);
};

#endif // UpdateGrade_Test_H



//////////////////

//use Qurl to connect with canvas
#include <QCoreApplication>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <Qssl>
#include <QTextStream>
#include <QFile>
using namespace std;

void sendRequest();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    sendRequest();
    return a.exec();

}

void sendRequest(){

    QFile file("out.json");
    // create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
      QNetworkRequest req( QUrl( QString("https://canvas.instructure.com/api/v1/courses?access_token=1030~HmnfpMmIn7wYqD48N0upMQfEbVMYsCPUIUcVnCnZyQrluVPp6l40GaHb3jsXvX3u") ) );
   // QNetworkRequest req( QUrl( QString("https://canvas.instructure.com/api/v1/courses/14812/assignments/55596?access_token=1030~HmnfpMmIn7wYqD48N0upMQfEbVMYsCPUIUcVnCnZyQrluVPp6l40GaHb3jsXvX3u") ) );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    QTextStream out(&file);
    if (reply->error() == QNetworkReply::NoError) {

        //success
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        file.write(reply->readAll());
        qDebug() << "Success" <<reply->readAll();
        delete reply;

    }
    else {
        //failure
        qDebug() << "Failure" ;
        delete reply;
    }
}


//////////////////////
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
         String Student_ID[100];
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
        char *greads_file_dir;//the grades file path, the Homework Automation group should provide
        grade_info *gradeList;
        String courseId;
        string AssignmentsId;
        string userId;
	double grade;
        static string auth;//the taken access of Canvas
        string update_Api;
        int Post_size;
  public:
        Canvas_Update(char *greads_file_dir,string courseId,string AssignmentsId, string auth,int Post_size);//construction function
        void getGradeInfo(*greads_file_dir);//convert the grades data into json
        void writeRequest(grade_info *gradeList,int Post_size);//write the request
        bool sendRequest(string auth, string update_Api);//send the request to Canvas
};

	
	
#include <UpdateGrade_Test.h>

int main(){
  _uploadManager = new QNetworkAccessManager(this);
  connect(_uploadManager,SIGNAL(finished(QNetworkReply*)),SLOT(replyFinished(QNetworkReply*)));
  m_buf = NULL;

  // reading from a json file and writing to a datastream
  QFile file("d:/update.json");
  file.open(QIODevice::ReadOnly);//open the json file in local
  int file_len = file.size();//aquire the size of file
  QDataStream in(&file);//initialize a datastream
  m_buf = new char[file_len];
  in.readRawData( m_buf, file_len);//start to read the json file
  file.close();

  // Make a request
  QNetworkRequest request(QUrl(tr("https://canvas.instructure.com/api/v1/courses/14812/assignments/55596?access_token=1030~cskoY40hPR86qHQM7PdGbjbkoqx93k8AzG3Y0uzEH21FXny2wfAnakD7TzjjnKHR")));
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");
  QByteArray arr = QByteArray(m_buf, file_len);
  _reply = _uploadManager->post(request , arr);
  connect(_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(upLoadError(QNetworkReply::NetworkError)));
  connect(_reply, SIGNAL(uploadProgress ( qint64 ,qint64 )), this, SLOT( OnUploadProgress(qint64 ,qint64 )));
  return 0;
}



