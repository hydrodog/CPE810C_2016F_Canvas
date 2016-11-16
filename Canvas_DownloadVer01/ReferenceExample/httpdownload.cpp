
#include "HttpDownload.h"

HttpDownload::HttpDownload(QObject * parent)
{
  http = new QHttp(this);
  httpDown = new QHttp(this);
  connect(httpDown, SIGNAL(requestFinished(int,bool)),
     this, SLOT(httpRequestFinish(int,bool)));
  connect(httpDown,SIGNAL(readyRead(QHttpResponseHeader)),
     this, SLOT(httpDownloadReadReady(QHttpResponseHeader)));
  connect(httpDown, SIGNAL(dataReadProgress(int,int)),
     this, SIGNAL(downloadProgress(int,int)));
  connect(http, SIGNAL(readyRead(QHttpResponseHeader)),
     this, SLOT(httpReadReady(QHttpResponseHeader)));

  strTmpDownDir = ".tmp_down/"; //定义下载文件的临时目录
  strBakDir = ".tmp_bak/"; //定义备份文件所在的临时目录
}

void HttpDownload::setDownloadTempFolder(QString folderName)
{
  if(folderName != ""){
    strTmpDownDir = getFolderName(folderName);
  }
}

QString HttpDownload::getFolderName(QString folderName)
{
  QString strResult = "";
  if(folderName != ""){
    strResult = folderName;
    if(!strResult.endsWith("/")){
      strResult = strResult.append("/");
    }
  }

  return strResult;
}

QString HttpDownload::getFolderPath(QString filePath)
{
    QString strResult = "";
    if(filePath != ""){
        QFileInfo fileInfo (filePath);
        strResult = fileInfo.path();
    }

    return strResult;
}

void HttpDownload::setBackupTempFolder(QString folderName)
{
  if(folderName != ""){
    strBakDir = getFolderName(folderName);
  }
}

void HttpDownload::backupFile(QString filePath)
{
  QString strDestDir = strBakDir + filePath;
  createDirectory(strDestDir);    /**< 创建备份文件所在的目录(包含自身的目录结构) */
  QFileInfo sourceFile(filePath);
  QFile::copy(filePath, strDestDir); /**< 进行文件copy */
}

void HttpDownload::restoreBackupFiles()
{
  copyDirectoryFiles(QDir(strBakDir), QDir::current(), true);
  removeDirectory(strBakDir);
}

void HttpDownload::deleteDownloadTempFiles()
{
  removeDirectory(strTmpDownDir);
}

void HttpDownload::download(QUrl url, QString target)
{
  QString strDownFolder = strTmpDownDir + target;
  createDirectory(strDownFolder);
  initHttp(httpDown, url, false);
  QString strfileName = getFileName(url);
  if(strfileName.isEmpty()){
    strfileName = "index.html";
  }

  //将文件下载到临时目录中(在文件名的前面添加临时目录的名称)
  strfileName = getFolderName(getFolderPath(strDownFolder)).append(strfileName);
  file = new QFile();
  file->setFileName(strfileName);
  if(!file->open(QIODevice::WriteOnly)){
    deleteFile(file);
    return;
  }
  QByteArray path = QUrl::toPercentEncoding(url.path(), "!$&'()*+,;=:@/");
  httpid = httpDown->get(path,file);
}

void HttpDownload::createDirectory(QString target){
  if(target == "")
    return;

  int idx = target.lastIndexOf("/");
  QString strDir = target.mid(0,idx);
  QDir dir;
  dir.mkpath(strDir);
}

void HttpDownload::initHttp(QHttp *myhttp, QUrl url, bool isNew)
{
  if(isNew){
    myhttp = new QHttp(this);
  }
  QHttp::ConnectionMode mode = url.scheme().toLower() == "https"
    ? QHttp::ConnectionModeHttps : QHttp::ConnectionModeHttp;

  myhttp->setHost(url.host(), mode, url.port() == -1 ? 80 : url.port());
}

void HttpDownload::beginHttpRequest(QUrl url, QString requestData)
{
  initHttp(http, url, false);
  header = QHttpRequestHeader("POST",url.toString());
  header.setContentType("application/x-www-form-urlencoded");
  http->request(header,requestData.toUtf8());
}

void HttpDownload::finishDownload()
{
  /// 将临时目录中的文件，copy到当前目录中
  copyDirectoryFiles(QDir(strTmpDownDir), QDir::current(), true);
  removeDirectory(strTmpDownDir);
  removeDirectory(strBakDir);
}

void HttpDownload::httpRequestFinish(int requestID, bool error)
{

  if(error){
    //removeDirectory(strTmpDownDir);
    //removeDirectory(strBakDir);

    qDebug() << "error" << endl;
  }
  else{
      file->flush();
      file->close();
      emit downFinish();
  }

  if(httpid != requestID){
    return;
  }

  file->flush();
  file->close();
}

void HttpDownload::httpDownloadReadReady(const QHttpResponseHeader &resp)
{
  file->write(httpDown->readAll());
}

void HttpDownload::httpReadReady(const QHttpResponseHeader &resp)
{
  QString strResult = QString(http->readAll());
  emit getHttpResponse(strResult);
}

QString HttpDownload::getFileName(QString path)
{
  QFileInfo fileInfo (path);
  QString strFileName = fileInfo.fileName();
  return strFileName;
}

QString HttpDownload::getFileName(QUrl url)
{
  return getFileName(url.path());
}

void HttpDownload::deleteFile(QFile *myfile)
{
  myfile->close();
  delete myfile;
  myfile = NULL;
}

void HttpDownload::deleteHttp(QHttp *myhttp)
{
  myhttp->close();
  delete myhttp;
  myhttp = NULL;
}

bool HttpDownload::copyDirectoryFiles(const QDir &fromDir,
                 const QDir &toDir,
                 bool coverFileIfExist)
{
  QDir sourceDir = fromDir;
  QDir targetDir = toDir;
  if(!targetDir.exists()){    /**< 如果目标目录不存在，则进行创建 */
    if(!targetDir.mkdir(toDir.absolutePath()))
      return false;
  }

  QFileInfoList fileInfoList = sourceDir.entryInfoList();
  foreach(QFileInfo fileInfo, fileInfoList){
    if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
      continue;

    if(fileInfo.isDir()){    /**< 当为目录时，递归的进行copy */
      if(!copyDirectoryFiles(fileInfo.filePath(),
             targetDir.filePath(fileInfo.fileName()),
             coverFileIfExist))
    return false;
    }
    else{            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
      if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){
    targetDir.remove(fileInfo.fileName());
      }

      /// 进行文件copy
      if(!QFile::copy(fileInfo.filePath(),
         targetDir.filePath(fileInfo.fileName()))){
    return false;
      }
    }
  }
  return true;
}

bool HttpDownload::removeDirectory(QString dirName)
{
  QDir dir(dirName);
  QString tmpdir = "";
  if(!dir.exists()){
    return false;
  }

  QFileInfoList fileInfoList = dir.entryInfoList();
  foreach(QFileInfo fileInfo, fileInfoList){
    if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
      continue;

    if(fileInfo.isDir()){
      tmpdir = dirName + ("/") + fileInfo.fileName();
      removeDirectory(tmpdir);
      dir.rmdir(fileInfo.fileName()); /**< 移除子目录 */
    }
    else if(fileInfo.isFile()){
      QFile tmpFile(fileInfo.fileName());
      dir.remove(tmpFile.fileName()); /**< 删除临时文件 */
    }
    else{
      ;
    }
  }

  dir.cdUp(); //返回上级目录，因为只有返回上级目录，才可以删除这个目录
  if(dir.exists(dirName)){
    if(!dir.rmdir(dirName))
      return false;
  }
  return true;
}

HttpDownload::~HttpDownload()
{
  if(file){
    deleteFile(file);
  }

  if(http){
    deleteHttp(http);
  }

  if(httpDown){
    deleteHttp(httpDown);
  }

}
