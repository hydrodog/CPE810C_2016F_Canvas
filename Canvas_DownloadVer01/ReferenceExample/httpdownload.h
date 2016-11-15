#ifndef HTTPDOWNLOAD_H
#define HTTPDOWNLOAD_H

#include <QFile>
//#include <QHttp>
#include <QUrl>
#include <QString>
#include <QtNetwork>
//#include <QHttpResponseHeader>
#include <QDebug>
#include <QDir>
#include <QMessageBox>


/**
 * Http下载类
 *
 */
class HttpDownload : public QObject{

  Q_OBJECT
  public:

  /**
   * 构造函数
   *
   * @param parent 父窗体ID
   *
   */
  HttpDownload(QObject* parent=0);

  /**
   * 进行下载
   *
   * @param url 下载的URL地址
   * @param target 下载目录，或者文件(默认为空，则下载在临时目录.tmp_down目录下)
   *
   * 说明：当该下载操作成功，仅将需要下载的文件下载到
   * 当前目录下的 .tmp_down临时目录中
   * (如果想更改临时目录的名称，需要在调用此方法前调用
   * setDownloadTempFloder(QString)方法，更改临时目录名称)
   *
   * 如果您需要将文件从临时目录中移动到当前目录中，
   * 并删除该临时目录，需要调用finishDownload方法。
   *
   * target参数，为下载的时文件所存放的路径
   * 如target为/update/down/ 则下载的文件将会在
   * 当前目录下创建update/down目录结构，（注意参数中的最后一定要带上‘/’）
   * 将url路径指定的文件保存在此目录下。
   *
   * 另外当target为 /update/down/test.jpg,
   * 则系同样会创建/update/down目录
   * 将url路径指定的文件保存在此目录下
   */
  void download(QUrl url, QString target = "");

  /**
   * 进行HTTP请求
   *
   * @param url 进行HTTP请求的URL
   * @requestData 请求的数据
   *
   * 说明：当调用该方法时，如果该方法执行成功，将会
   * 发出 getHttpResponse(QString response)信号
   */
  void beginHttpRequest(QUrl url, QString requestData = "");

  /**
   * 完成下载的文件
   *
   * 说明：将下载的文件进行替换操作 & 删除下载的文件
   *
   */
  void finishDownload();

  /**
   * 设置下载临时目录的名称
   *
   * @param folderName 目录的名称
   *
   * 备注：建议folderName为一级目录名称 如：tmp
   * 注意：不要和setBackupTempFolder设置为同一个名称
   */
  void setDownloadTempFolder(QString folderName = ".tmp_down");

  /**
   * 设置备份文件所在的目录
   *
   * @param folderName 目录的名称
   *
   * 备注：建议folderName为一级目录名称如：bak
   * 注意：不要和setDownloadTempFolder设置为同一个名称
   */
  void setBackupTempFolder(QString folderName = ".tmp_bak");

  /**
   * 备份文件
   *
   * @param filePath 文件的相对路径
   *
   * 说明：如果路径中存在目录，则自动创建相应的目录
   * 备注：此方法只能针对一个文件的相对路径，而不能针对多个文件
   */
  void backupFile(QString filePath);

  /**
   * 还原已经备份的文件
   *
   * 说明：还原备份的文件，删除备份文件的目录
   */
  void restoreBackupFiles();

  /**
   * 删除下载的临时文件
   *
   */
  void deleteDownloadTempFiles();

  /**
   * 获取文件名
   *
   * @param path 文件的路径
   *
   * @return 文件名
   */
  QString getFileName(QString path);

  /**
   * 析构函数
   *
   */
  ~HttpDownload();

signals:

  /**
   * 下载文件的进度
   *
   * @param done 当前的下载量
   * @param total 下载的总量
   */
  void downloadProgress(int done, int total);

  /**
   * 获取HTTP请求的响应字符串
   *
   * @response HTTP响应字符串
   */
  void getHttpResponse(QString response);

  /**
   * 下载文件完成的信号
   *
   */
  void downFinish();

 private slots:

  /**
   * 当HTTP请求完成时
   *
   * @param requestID 请求的ID
   * @param error 返回请求是否成功
   */
  void httpRequestFinish(int requestID, bool error);

  /**
   * 当HTTP请求开始时
   *
   * @param resp HTTP响应头对象
   */
  void httpReadReady(const QHttpResponseHeader &resp);

  /**
   * 当HTTP请求开始下载文件时
   *
   * @param resp HTTP响应头对象
   */
  void httpDownloadReadReady(const QHttpResponseHeader &resp);

 private:
  QHttp *http;
  QHttp *httpDown;
  QFile *file;
  QHttpRequestHeader header;
  int httpid;
  QString strTmpDownDir; //定义下载文件的临时目录
  QString strBakDir; //定义备份文件所在的临时目录

  /**
   * 根据目录名称，获取带有'/'结束的目录名称
   *
   * @param folderName 目录名称
   *
   * @return 带有'/'结束的目录名称
   */
  QString getFolderName(QString folderName);


  QString getFolderPath(QString filePath);

  /**
   * 删除文件指针
   *
   * @param myfile 文件指针
   */
  void deleteFile(QFile *myfile);

  /**
   * 删除Http指针
   *
   * @param myhttp HTTP请求指针
   */
  void deleteHttp(QHttp *myhttp);

  /**
   * 初始化Http对象
   *
   * @param myhttp http指针
   * @url 连接的URL
   * @isNew 是否实例化myhttp
   */
  void initHttp(QHttp *myhttp, QUrl url, bool isNew);

  /**
   * 获取文件名
   *
   * @param url Http的Url
   *
   * @return 文件名
   */
  QString getFileName(QUrl url);

  /**
   * copy一个目录中的文件到另外一个目录
   *
   * @param fromDir 源目录
   * @param toDir 目标目录
   * @param coverFileIfExist 当目标目录中存在同名文件，是否进行覆盖；默认进行覆盖
   *
   * @return copy成功：true;copy失败：false
   */
  bool copyDirectoryFiles(const QDir &fromDir,
             const QDir &toDir,
             bool coverFileIfExist = true);

  /**
   * 删除目录
   *
   * @param dirName 目录名称
   *
   * @return 删除目录成功：true;删除目录失败：false
   */
  bool removeDirectory(QString dirName);

  /**
   * 创建目录
   *
   * @param target 目录的路径
   * 说明：当target为空则不做任何操作，直接返回；
   * 当传递的参数为aa/bb/则会在当前目录上创建aa/bb/目录(最后的‘/’不能省掉)
   * 当传递的参数为aa/bb/cc/dd.txt则会在当前的目录下创建aa/bb/cc目录
   *
   * 注：此方法主要是被download(QUrl url, QString target)
   * 调用以创建相关的目录结构
   */
  void createDirectory(QString target);
};

#endif
