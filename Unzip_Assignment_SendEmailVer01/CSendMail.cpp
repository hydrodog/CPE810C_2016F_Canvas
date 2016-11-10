
#include "StdAfx.h"
#include "CSendMail.h"
#include "winsock2.h"
#pragma comment(lib,"WSOCK32")
#pragma comment(lib, "ws2_32")

CSendMail::CSendMail(void)
{
    m_pcFileBuff=NULL;
    memset(m_cSendBuff,0,sizeof(m_cSendBuff));
    memset(m_cReceiveBuff,0,sizeof(m_cReceiveBuff));
}


CSendMail::~CSendMail(void)
{
    DeleteAllPath();
}

void CSendMail::Char2Base64(unsigned char* dest, unsigned char* src, int srclen)
{
	int sign = 0;

	const unsigned char EncodeIndex[] = {
		'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
		'Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f',
		'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
		'w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/'
	};

	for (int i = 0; i!= srclen; i++,src++,dest++)
	{
		switch(sign)
		{
		case 0:
			*(dest) = EncodeIndex[*src >> 2];
			break;
		case 1:
			*dest = EncodeIndex[((*(src-1)  & 0x03) << 4) | (((*src) & 0xF0) >> 4)];
			break;
		case 2:
			*dest = EncodeIndex[((*(src-1) &0x0F) << 2) | ((*(src) & 0xC0) >> 6)];
			*(++dest) = EncodeIndex[(*(src) &0x3F)];
			break;
		}
		(sign == 2)?(sign = 0):(sign++);
	}
	switch(sign)
	{
	case 0:
		break;
	case 1:
		*(dest++) = EncodeIndex[((*(src-1)  & 0x03) << 4) | (((*src) & 0xF0) >> 4)];
		*(dest++) = '=';
		*(dest++) = '=';
		break;
	case 2:
		*(dest++) = EncodeIndex[((*(src-1) &0x0F) << 2) | ((*(src) & 0xC0) >> 6)];
		*(dest++) = '=';
		break;
	default:
		break;
	}
}


   

bool CSendMail::CReateSocket(SOCKET &sock)
{
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD( 2, 2 );
    err = WSAStartup( wVersionRequested, &wsaData );
    if ( err != 0 )
    {
        return false;
    }
    if ( LOBYTE( wsaData.wVersion ) != 2 ||
        HIBYTE( wsaData.wVersion ) != 2 )
    {
        WSACleanup( );
        return false;
    }
    sock = socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
    if (sock == INVALID_SOCKET)
    {
        return false;
    }

    sockaddr_in servaddr;
    memset(&servaddr,0,sizeof(sockaddr_in));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(25);//usually it's port 25
    if(m_sMailInfo.m_pcIPName=="")
    {
        servaddr.sin_addr.s_addr = inet_addr(m_sMailInfo.m_pcIPAddr);//use ip address here directly
    }
    else
    {
        struct hostent *hp=gethostbyname(m_sMailInfo.m_pcIPName);//use a name
		if (hp == NULL)
		{
			DWORD dwErrCode =	GetLastError();
			return false;
		}
        servaddr.sin_addr.s_addr=*(int*)(*hp->h_addr_list);
    }


    int ret = connect(sock,(sockaddr*)&servaddr,sizeof(servaddr));//build the connection
    if (ret == SOCKET_ERROR)
    {
		DWORD dwErr = GetLastError();
        return false;
    }

    return true;
}


bool CSendMail::login(SOCKET &sock)
{
	char local_host[MAX_PATH];

	if ( gethostname(local_host, MAX_PATH) != 0 )
	{
		return false;
	}
    recv(sock,m_cReceiveBuff,1024,0);
    memset(m_cSendBuff,0,sizeof(m_cSendBuff));
	sprintf_s(m_cSendBuff,"HELO %s\r\n", local_host);


    send(sock,m_cSendBuff,strlen(m_cSendBuff),0);//start the chat
    recv(sock,m_cReceiveBuff,1024,0);
    if(m_cReceiveBuff[0]!='2' || m_cReceiveBuff[1]!='5' || m_cReceiveBuff[2]!='0')
    {
        return false;
    }

    memset(m_cSendBuff,0,sizeof(m_cSendBuff));
    sprintf_s(m_cSendBuff,"AUTH LOGIN\r\n");
    send(sock,m_cSendBuff,strlen(m_cSendBuff),0);//request to login
    recv(sock,m_cReceiveBuff,1024,0);
    if(m_cReceiveBuff[0]!='3' || m_cReceiveBuff[1]!='3' || m_cReceiveBuff[2]!='4')
    {
        return false;
    }

    memset(m_cSendBuff,0,sizeof(m_cSendBuff));
    Char2Base64((unsigned char*)m_cSendBuff,(unsigned char*)m_sMailInfo.m_pcUserName,strlen(m_sMailInfo.m_pcUserName));
    m_cSendBuff[strlen(m_cSendBuff)]='\r';
    m_cSendBuff[strlen(m_cSendBuff)]='\n';
    send(sock,m_cSendBuff,strlen(m_cSendBuff),0);//send the user's name
    recv(sock,m_cReceiveBuff,1024,0);
    if(m_cReceiveBuff[0]!='3' || m_cReceiveBuff[1]!='3' || m_cReceiveBuff[2]!='4')
    {
        return false;
    }

    memset(m_cSendBuff,0,sizeof(m_cSendBuff));
    Char2Base64((unsigned char*) m_cSendBuff,(unsigned char*) m_sMailInfo.m_pcUserPassWord,strlen(m_sMailInfo.m_pcUserPassWord));
    m_cSendBuff[strlen(m_cSendBuff)]='\r';
    m_cSendBuff[strlen(m_cSendBuff)]='\n';
    send(sock,m_cSendBuff,strlen(m_cSendBuff),0);//send the password
    recv(sock,m_cReceiveBuff,1024,0);
    if(m_cReceiveBuff[0]!='2' || m_cReceiveBuff[1]!='3' || m_cReceiveBuff[2]!='5')
    {
        return false;
    }
    return true;
}


bool CSendMail::SendHead(SOCKET &sock)
{
    int rt;
    memset(m_cSendBuff,0,sizeof(m_cSendBuff));
    sprintf_s(m_cSendBuff,"MAIL FROM:<%s>\r\n",m_sMailInfo.m_pcSender);
    rt=send(sock,m_cSendBuff,strlen(m_cSendBuff),0);

    if(rt!=strlen(m_cSendBuff))
    {
        return false;
    }
    recv(sock,m_cReceiveBuff,1024,0);

    memset(m_cSendBuff,0,sizeof(m_cSendBuff));
    sprintf_s(m_cSendBuff,"RCPT TO:<%s>\r\n",m_sMailInfo.m_pcReceiver);
    rt=send(sock,m_cSendBuff,strlen(m_cSendBuff),0);
    if(rt!=strlen(m_cSendBuff))
    {
        return false;
    }
    recv(sock,m_cReceiveBuff,1024,0);

    memset(m_cSendBuff,0,sizeof(m_cSendBuff));
    memcpy(m_cSendBuff,"DATA\r\n",strlen("DATA\r\n"));
    rt=send(sock,m_cSendBuff,strlen(m_cSendBuff),0);
    if(rt!=strlen(m_cSendBuff))
    {
        return false;
    }
    recv(sock,m_cReceiveBuff,1024,0);

    memset(m_cSendBuff,0,sizeof(m_cSendBuff));
    sprintf_s(m_cSendBuff,"From:\"%s\"<%s>\r\n",m_sMailInfo.m_pcSenderName,m_sMailInfo.m_pcSender);
    sprintf_s(&m_cSendBuff[strlen(m_cSendBuff)],150,"To:\"INVT.COM.CN\"<%s>\r\n",m_sMailInfo.m_pcReceiver);
    sprintf_s(&m_cSendBuff[strlen(m_cSendBuff)],150,"Subject:%s\r\nMime-Version: 1.0\r\nContent-Type: multipart/mixed;   boundary=\"INVT\"\r\n\r\n",m_sMailInfo.m_pcTitle);
    rt=send(sock,m_cSendBuff,strlen(m_cSendBuff),0);
    if(rt!=strlen(m_cSendBuff))
    {
        return false;
    }

    return true;
}

bool CSendMail::SendTextBody(SOCKET &sock)
{
    int rt;
    memset(m_cSendBuff,0,sizeof(m_cSendBuff));
    sprintf_s(m_cSendBuff,"--INVT\r\nContent-Type: text/plain;\r\n  charset=\"gb2312\"\r\n\r\n%s\r\n\r\n",m_sMailInfo.m_pcBody);
    rt=send(sock,m_cSendBuff,strlen(m_cSendBuff),0);
    if(rt!=strlen(m_cSendBuff))
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool CSendMail::SendFileBody(SOCKET &sock)
{
    int i;
    char* filePath;
    int rt;
    int len;
    int pt=0;
    char fileName[MAX_PATH];


    for(i=0;i<m_pcFilePathList.GetCount();i++)
    {
        pt=0;
        memset(fileName,0,MAX_PATH);
        filePath=m_pcFilePathList.GetAt(m_pcFilePathList.FindIndex(i));
        len=GetFileData(filePath);
        GetFileName(fileName,filePath);

        sprintf_s(m_cSendBuff,"--INVT\r\nContent-Type: application/octet-stream;\r\n  name=\"%s\"\r\nContent-Transfer-Encoding: base64\r\nContent-Disposition: attachment;\r\n  filename=\"%s\"\r\n\r\n",fileName,fileName);
        send(sock,m_cSendBuff,strlen(m_cSendBuff),0);
        while (pt<len)
        {
            memset(m_cSendBuff,0,sizeof(m_cSendBuff));
            Char2Base64( (unsigned char*) m_cSendBuff,(unsigned char*) &m_pcFileBuff[pt],min(len-pt,3000));
            m_cSendBuff[strlen(m_cSendBuff)]='\r';
            m_cSendBuff[strlen(m_cSendBuff)]='\n';
			rt=send(sock,m_cSendBuff,strlen(m_cSendBuff),0);
            pt+=min(len-pt,3000);
            if(rt!=strlen(m_cSendBuff))
            {
                return false;
            }
        }
        if(len!=0)
        {
            delete [] m_pcFileBuff;
        }
    }

    return true;
}

bool CSendMail::SendEnd(SOCKET &sock)
{
    sprintf_s(m_cSendBuff,"--INVT--\r\n.\r\n");
    send(sock,m_cSendBuff,strlen(m_cSendBuff),0);

    sprintf_s(m_cSendBuff,"QUIT\r\n");
    send(sock,m_cSendBuff,strlen(m_cSendBuff),0);
    closesocket(sock);
    WSACleanup();
    return true;
}


bool CSendMail::SendMail(SMailInfo &smailInfo)
{
    memcpy(&m_sMailInfo,&smailInfo,sizeof(smailInfo));
    if(m_sMailInfo.m_pcBody==NULL
        || m_sMailInfo.m_pcIPAddr==NULL
        || m_sMailInfo.m_pcIPName==NULL
        || m_sMailInfo.m_pcReceiver==NULL
        || m_sMailInfo.m_pcSender==NULL
        || m_sMailInfo.m_pcSenderName==NULL
        || m_sMailInfo.m_pcTitle==NULL
        || m_sMailInfo.m_pcUserName==NULL
        || m_sMailInfo.m_pcUserPassWord==NULL)
    {
        return false;
    }
    SOCKET sock;
    if(!CReateSocket(sock))//creat the socket
    {
        return false;
    }

    if(!login(sock))//login the mail account
    {
        return false;
    }

    if(!SendHead(sock))//send the head of mail
    {
        return false;
    }

    if(!SendTextBody(sock))//text body
    {
        return false;
    }


    if(!SendEnd(sock))//end the mail and the socket
    {
        return false;
    }

    return true;
}
