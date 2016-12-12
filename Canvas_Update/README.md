This repository is for the update part of EE810 Canvas group

In update section, Our job is to update the grade on Canvas. Through the Canvas API. 
Consider the inter-platform. We use the QT lib "Network" to make the HTTPS request.

Here is the main function of our project：

        Canvas_Update(QString courseId, QString AssignmentsId, QString auth);//construction function
        Canvas_Update(vector<grade_info> gradeList, QString courseId, QString AssignmentsId, QString auth);//construction function
        void convertData(vector<grade_info> dataList);	//convert the grades data into string type
        void sendRequest();//send the request to Canvas(When you  are ready)
        void addSingle(QString id, QString comment, QString grade);//add the single grade info and update
        void setAuth(QString auth); //set the Auth
        void setAuthByFile(QString path);//set the Auth by file
        void setCourseId(QString courseId);//set the course Id
        void setAssignmentsId(QString AssignmentsId);//set the AssignmentsId

And the data struct we need to update

        struct grade_info //define the single submission grades struct
        {
        QString Stu_ID;
        QString text_comment; //add a textual comment to the submission.
        QString posted_grade;//the grade of the submission

        /*the fellowing is the extra data we could put into the Canvas
        bool   group_comment;//whether or not this comment should be sent to the entire group(defaults to false).ignored if this is not a group assignment or if no text_comment is provided.
        string media_comment_id//add an audio/video comment to the submission. media comments can be added via this api
        string media_comment_type//type of media comment being added.allow audio, video
        int      comment_file_ids//Attach files to this comment that were previously uploaded using the Submission Comment API's files action
        string visibility//Whether this assignment is visible to the owner of the submission
        bool   excuse;//Sets the “excused” status of an assignment.*/
        };


Here is the example in the main.cpp, and the final code is in the CanvasUpdate filefolder.

        #include <QCoreApplication>
        #include <canvasupdate.h>

        QString test_auth = "Bearer 1030~4MvxMX4ZFH8LCUAe9pFKhNUwFc6o4PnsFny5vlO4sLdyExxx3B9SR3ULM2nzl211";

        grade_info stdtemp[3] = {
        {"7672","bad job!!!!!","3"},
        {"19850","bad job too!!!!!!","3"},
        {"19880","You are much worse!!!!!!","33"}
        };



        int main(int argc, char *argv[])
        {
        QCoreApplication a(argc, argv);
        vector<grade_info> gradelists;
        for(int i=0;i<3;i++)
        {
                gradelists.push_back(stdtemp[i]);
        }
        Canvas_Update update1(gradelists,"133","46024",test_auth);
        update1.sendRequest();
        //    Canvas_Update update2("133","46024", "test");
        //    update2.setAuthByFile("auth.txt");
        //    update2.addSingle("7672","just joke","59");

        return a.exec();
        }




