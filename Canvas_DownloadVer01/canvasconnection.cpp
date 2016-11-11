#include "canvasconnection.h"
#include <QTextCodec>
#include <iostream>
#include <QtNetwork>

canvasConnection::canvasConnection(QObject *parent) :
    QObject(parent)
{
    m_pNetworkManager = new QNetworkAccessManager(this);
    m_pNetworkReply = NULL;
}

//Send network requests
void canvasConnection::sendRequest(const QString &strUrl)
{
	m_strUrl = strUrl;
	//Create custom temporary event loop on stack
    QEventLoop eventLoop;
	//Open a file
	QFile file("out.json");
	//Send request to Canvas by using token.
    QNetworkRequest netRequest;
    //Set the information of url.
    netRequest.setUrl(QUrl(strUrl));
    /*Posts a request to obtain the contents of the target request and
    returns a new QNetworkReply object opened for reading*/
    m_pNetworkReply =m_pNetworkManager->get(netRequest);
    //Signal when the network requests end
    QObject::connect(m_pNetworkManager,SIGNAL(finished(QNetworkReply*)),&evenLoop,SLOT(quit()));
	// blocks stack until "finished()" has been called
	eventLoop.exec();
	QTextStream out(&file);
    if (m_pNetworkReply->error() == QNetworkReply::NoError) {
        //success
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        file.write(m_pNetworkReply->readAll());
        qDebug() << "Success" <<m_pNetworkReply->readAll();
		//release memory
        delete m_pNetworkReply;
    }
    else {
        //failure
        qDebug() << "Failure" ;
		//release memory
        delete m_pNetworkReply;
    }
}
