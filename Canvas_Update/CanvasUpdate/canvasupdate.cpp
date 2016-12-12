#include <canvasupdate.h>

Canvas_Update::Canvas_Update(vector<grade_info> gradeList, QString courseId, QString AssignmentsId, QString auth)
{
    this->gradeList = gradeList;
    this->courseId = courseId;
    this->AssignmentsId = AssignmentsId;
    this->auth = auth;
    this->update_API = "https://sit.instructure.com/api/v1/courses/"+courseId+"/assignments/"+AssignmentsId+"/submissions/update_grades";
    convertData(this->gradeList);

}

void Canvas_Update::convertData(vector<grade_info> dataList)
{
    reqBody = "{\"grade_data\":{";
    for (size_t i = 0; i < dataList.size(); i++)
    {
        reqBody.append("\"");
        reqBody.append(dataList[i].Stu_ID);
        reqBody.append("\":{\"posted_grade\" :\"");
        reqBody.append(dataList[i].posted_grade);
        reqBody.append("\",\"text_comment\" :\"");
        reqBody.append(dataList[i].text_comment);
        reqBody.append("\"}");
        if(i!=(dataList.size()-1))
        {
          reqBody.append(",");
        }
    }
    reqBody.append("}}");
}


void Canvas_Update::sendRequest()
{
    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QByteArray postdata;
    postdata.append(reqBody);
    qDebug() << postdata<<'\n';
    // the HTTP request
    QNetworkRequest req(QUrl(this->update_API));
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    req.setRawHeader("Accept","application/json");
    req.setRawHeader("Authorization","Bearer 1030~4MvxMX4ZFH8LCUAe9pFKhNUwFc6o4PnsFny5vlO4sLdyExxx3B9SR3ULM2nzl211");
    QNetworkReply *reply = mgr.post(req,postdata);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError) {
        QString result = reply->readAll();
        QFile json_res("response.json");
        json_res.open(QFile::WriteOnly);
        QJsonDocument doc = QJsonDocument::fromJson(result.toUtf8());
        json_res.write(doc.toJson());

        qDebug() << "Success"<<doc;
        delete reply;
    }
    else {
        //failure
        qDebug() << "Failure"<<reply->errorString() ;
        delete reply;
    }
}
