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

