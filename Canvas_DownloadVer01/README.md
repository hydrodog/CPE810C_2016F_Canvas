# Canvas-Download

**MUST SEE: In the .pro file, please add 'QT += network' and 'QT += widgets'. Also, you may meet some problems about OpenSSL:
	
	qt.network.ssl: QSslSocket: cannot call unresolved function ERR_get_error.
	qt.network.ssl: QSslSocket: cannot call unresolved function TLSv1_client_method
	qt.network.ssl: QSslSocket: cannot call unresolved function SSL_CTX_new
	qt.network.ssl: QSslSocket: cannot call unresolved function SSL_library_init
	qt.network.ssl: QSslSocket: cannot call unresolved function ERR_get_error
Please fild two file 'libeay32.dll' and 'ssleay32.dll' under D:\Qt\Qt5.7\Tools\mingw530_32\opt\bin. Then copy them and put them under D:\Qt\Qt5.7\5.7\mingw53_32\bin. The problems are solved.**

/*
@author = Shengjie Hu, Mingju He, Jingyi Hu. 


task : Writing code that is able to download files from Canvas in Qt.
*/  
 
 
**Date:2016.10.28～2016.11.4 ** 
   
    List all the function we will need to download files from Canvas and write 2 basic classes 
    function framework.  
    
    canvasconnection.cpp
    
    canvasconnection.h  */


**Date:2016.11.4~Date.11.11 **

     We compare 2 ways to send requests to https and decide to use QNetworkAccessManager rather than libcurl. 
     The code now can get access to Canvas by using token in Qt and download some infomation into a file.
     
     
     Mingju He upload the request file which can connect to Canvas and  Jingyi Hu find how to connect Canvas
     byusing cUrl.   Our teamleader Shengjie Hu write the full classes we will need and fix some bugs. 
     
     request  file 
     canvasconnection.cpp
     canvasconnection.h  
     
     TODO:we are going to wrtie codes that can analyze JSON and try to find api that could download all students assignments. (submission)

**Date:2016.11.12~2016.11.14**  

	Shengjie Hu and Mingju He try to use API to download submissions.

	TODO:Try to find right api that could download all students submissions and classify them. 
	
**Date:2016.11.15~2016.11.17**  

	We connect with other team to determine what kind of data they want.
	
	Also, we get the right Url to download submissions, but we should login first. We are trying to log in canvas first.

**Date:2016.11.19**  

	We can extract json data.
	
	TODO:Try to find right api that could download all students submissions and classify them.
