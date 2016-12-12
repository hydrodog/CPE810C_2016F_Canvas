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

Canvas_Update::Canvas_Update(QString courseId, QString AssignmentsId, QString auth="Bearer 1030~4MvxMX4ZFH8LCUAe9pFKhNUwFc6o4PnsFny5vlO4sLdyExxx3B9SR3ULM2nzl211")
{
    this->courseId = courseId;
    this->AssignmentsId = AssignmentsId;
    this->auth = auth;
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
    req.setRawHeader("Authorization",this->auth.toUtf8());
    QNetworkReply *reply = mgr.post(req,postdata);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError) {
        QString result = reply->readAll();
        QFile json_res("Process_response.json");
        json_res.open(QFile::WriteOnly);
        QJsonDocument doc = QJsonDocument::fromJson(result.toUtf8());
        json_res.write(doc.toJson());
        qDebug() << "Update Success"<<'\n'<<"Here is the return progress:  "<<doc;
        delete reply;
        json_res.close();
    }
    else {
        //failure
        qDebug() << "Failure"<<reply->errorString() ;
        delete reply;
    }
}

void Canvas_Update::addSingle(QString id, QString comment, QString grade)
{
    QEventLoop eventLoop;
    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QByteArray postdata;
    postdata +="{\"comment\":{\"text_comment\" : \""+ comment +"\"},\"submission\":{\"posted_grade\": \""+grade+"\"} }";
    // the HTTP request
    QString APIUrl =  "https://sit.instructure.com/api/v1/courses/" + this->courseId + "/assignments/" + this->AssignmentsId + "/submissions/"+id;
   // QNetworkRequest req( QUrl( APIUrl ));
    QNetworkRequest req(APIUrl);
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    req.setRawHeader("Accept","application/json");
    req.setRawHeader("Authorization",this->auth.toUtf8());
    QNetworkReply *reply = mgr.put(req,postdata);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError) {
        //success
        QString result = reply->readAll();
        QFile json_res("Single_response.json");
        json_res.open(QFile::WriteOnly);
        QJsonDocument doc = QJsonDocument::fromJson(result.toUtf8());
        QJsonObject jsobj = doc.object();
        QJsonValue grade = jsobj.value("grade");
        QJsonValue gradeTime = jsobj.value("graded_at");
        json_res.write(doc.toJson());
        qDebug() << "Update Success"<<"\n"<<"changed grade: " <<grade<<'\n'<<"graded_at"<<gradeTime;
        delete reply;
        json_res.close();
    }
    else {
        //failure
        qDebug() << "Failure"<<reply->errorString() ;
        delete reply;
    }
}

void Canvas_Update::setCourseId(QString courseId)
{
    this->courseId = courseId;
}

void Canvas_Update::setAssignmentsId(QString AssignmentsId)
{
    this->AssignmentsId = AssignmentsId;
}

void Canvas_Update::setAuth(QString auth)
{
    this->auth = auth;
}

void Canvas_Update::setAuthByFile(QString path)
{
    QFile authFile(path);
    if (authFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&authFile);
       while (!in.atEnd())
       {
          QString authInFile = in.readLine();
          qDebug()<<authInFile;
          this->auth = authInFile;
       }
       authFile.close();
    }

}


