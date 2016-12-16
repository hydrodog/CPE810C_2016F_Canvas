#ifndef CANVASUPDATE_H
#define CANVASUPDATE_H
#include <iostream>
#include <QtNetwork>
#include <QString>
#include <QFile>
#include <vector>
#include <String>
using namespace std;

struct grade_information //define the single submission grades struct
{
    double  Stu_ID;
    string text_comment; //add a textual comment to the submission.
    double posted_grade;//the grade of the submission

    grade_information(double stu_id, double sub_grade, string sub_comment) :
        Stu_ID(stu_id), posted_grade(sub_grade), text_comment(sub_comment) {}

    /*the fellowing is the extra data we could put into the Canvas
    bool   group_comment;//whether or not this comment should be sent to the entire group(defaults to false).ignored if this is not a group assignment or if no text_comment is provided.
    string media_comment_id//add an audio/video comment to the submission. media comments can be added via this api
    string media_comment_type//type of media comment being added.allow audio, video
    int      comment_file_ids//Attach files to this comment that were previously uploaded using the Submission Comment API's files action
    string visibility//Whether this assignment is visible to the owner of the submission
    bool   excuse;//Sets the “excused” status of an assignment.*/
};

//String to String
//std::string str = "Hello world";
//QString qstr = QString::fromStdString(str);


//double valueAsDouble = 1.2;
//QString valueAsString = QString::number(valueAsDouble);


struct grade_info //define the single submission grades struct
{
    QString Stu_ID;
    QString text_comment; //add a textual comment to the submission.
    QString posted_grade;//the grade of the submission
    grade_info(grade_information grade)
    {
        Stu_ID = QString::number(grade.Stu_ID);
        text_comment = QString::fromStdString(grade.text_comment);
        posted_grade = QString::number(grade.posted_grade);
    }
    grade_info(QString id, QString comment, QString grade):Stu_ID(id),text_comment(comment),posted_grade(grade){}


    /*the fellowing is the extra data we could put into the Canvas
    bool   group_comment;//whether or not this comment should be sent to the entire group(defaults to false).ignored if this is not a group assignment or if no text_comment is provided.
    string media_comment_id//add an audio/video comment to the submission. media comments can be added via this api
    string media_comment_type//type of media comment being added.allow audio, video
    int      comment_file_ids//Attach files to this comment that were previously uploaded using the Submission Comment API's files action
    string visibility//Whether this assignment is visible to the owner of the submission
    bool   excuse;//Sets the “excused” status of an assignment.*/
};
//This is Shizhe Zhou's auth, The user need to set their own
//Testing example

class Canvas_Update
{
private:
    //grade_info *gradeList;//the grades file path, the Homework Automation group should provide
    vector<grade_info> gradeList;
    //vector<string> stuIdList;
    QString reqBody;
    QString courseId;
    QString AssignmentsId;
    QString auth;//the Grader's taken access of Canvas
    QString update_API;
public:
    Canvas_Update(QString courseId, QString AssignmentsId, QString auth);
    Canvas_Update(vector<grade_info> gradeList, QString courseId, QString AssignmentsId, QString auth);//construction function
    Canvas_Update(vector<grade_information> gradeList, long courseId,long AssignmentsId);

    //void getGradeInfo(char *greads_file_dir);
    void convertData(vector<grade_info> dataList);	//convert the grades data into string type
    void sendRequest();//send the request to Canvas
    void addSingle(QString id, QString comment, QString grade);
    void setAuth(QString auth);
    void setAuthByFile(QString path);
    void setCourseId(QString courseId);
    void setAssignmentsId(QString AssignmentsId);



};


#endif // CANVASUPDATE_H
