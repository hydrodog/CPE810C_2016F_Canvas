#include "stdlib.h"
#include "smtp.h"
#include <iostream>
using namespace std;
#pragma  comment(lib, "ws2_32.lib") //con ws2_32.lib

//base64 code
char* CSmtp::base64Encode(char const* origSigned, unsigned origLength)
{
    unsigned char const* orig = (unsigned char const*)origSigned; // in case any input bytes have the MSB set
    if (orig == NULL) return NULL;

    unsigned const numOrig24BitValues = origLength / 3;
    bool havePadding = origLength > numOrig24BitValues * 3;
    bool havePadding2 = origLength == numOrig24BitValues * 3 + 2;
    unsigned const numResultBytes = 4 * (numOrig24BitValues + havePadding);
    char* result = new char[numResultBytes + 3]; // allow for trailing '/0'

    // Map each full group of 3 input bytes into 4 output base-64 characters:
    unsigned i;
    for (i = 0; i < numOrig24BitValues; ++i)
    {
        result[4 * i + 0] = base64Char[(orig[3 * i] >> 2) & 0x3F];
        result[4 * i + 1] = base64Char[(((orig[3 * i] & 0x3) << 4) | (orig[3 * i + 1] >> 4)) & 0x3F];
        result[4 * i + 2] = base64Char[((orig[3 * i + 1] << 2) | (orig[3 * i + 2] >> 6)) & 0x3F];
        result[4 * i + 3] = base64Char[orig[3 * i + 2] & 0x3F];
    }

    // Now, take padding into account.  (Note: i == numOrig24BitValues)
    if (havePadding)
    {
        result[4 * i + 0] = base64Char[(orig[3 * i] >> 2) & 0x3F];
        if (havePadding2)
        {
            result[4 * i + 1] = base64Char[(((orig[3 * i] & 0x3) << 4) | (orig[3 * i + 1] >> 4)) & 0x3F];
            result[4 * i + 2] = base64Char[(orig[3 * i + 1] << 2) & 0x3F];
        }
        else
        {
            result[4 * i + 1] = base64Char[((orig[3 * i] & 0x3) << 4) & 0x3F];
            result[4 * i + 2] = '=';
        }
        result[4 * i + 3] = '=';
    }

    result[numResultBytes] = '\0';
    return result;
}
CSmtp::CSmtp(void)
{
    this->content = "";
    this->port = 25;
    this->user = "";
    this->pass = "";
    this->targetAddr = "";
    this->title = "";
    this->domain = "";

    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD(2, 1);
    err = WSAStartup(wVersionRequested, &wsaData);
    this->sockClient = 0;

}

CSmtp::~CSmtp(void)
{
    DeleteAllAttachment();
    closesocket(sockClient);
    WSACleanup();
}


CSmtp::CSmtp(
    int port,
    std::string srvDomain,
    std::string userName,
    std::string password,
    std::string targetEmail,
    std::string emailTitle,
    std::string content
    )
{
    this->content = content;
    this->port = port;
    this->user = userName;
    this->pass = password;
    this->targetAddr = targetEmail;
    this->title = emailTitle;
    this->domain = srvDomain;
    cout<<"hello"<<endl;
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD(2, 1);
    err = WSAStartup(wVersionRequested, &wsaData);
    this->sockClient = 0;
}

bool CSmtp::CreateConn()
{
    //for set socket,init the envernment
    SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0); //set socket
    SOCKADDR_IN addrSrv;
    HOSTENT* pHostent;
    pHostent = gethostbyname(domain.c_str());  //get domain information

    addrSrv.sin_addr.S_un.S_addr = *((DWORD *)pHostent->h_addr_list[0]);    //get smtp server internet ip address
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(port);
    int err = connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));   //send requset to serve
    if (err != 0)
    {
         printf("connect fail\n");
        return false;

    }
    this->sockClient = sockClient;
    if (false == Recv())
    {
        printf("connect fail\n");
        return false;
    }
    return true;
}

bool CSmtp::Send(std::string &message)
{
    int err = send(sockClient, message.c_str(), message.length(), 0);
    if (err == SOCKET_ERROR)
    {
        cout<<"hierr";
        return false;
    }
    std::string message01;
    return true;
}

bool CSmtp::Recv()
{
    memset(buff, 0, sizeof(char)* (MAXLEN + 1));
    int err = recv(sockClient, buff, MAXLEN, 0); //recive data
    if (err == SOCKET_ERROR)
    {
        return false;
    }
    buff[err] = '\0';
    return true;
}

int CSmtp::Login()
{
    cout<<"33333";
    std::string sendBuff;
    sendBuff = "EHLO ";
    sendBuff += user; // this part need to use telnet decate
    sendBuff += "\r\n";

    if (false == Send(sendBuff) || false == Recv()) //send and recive
    {

        return 1; //1 is because of the internet
    }

    sendBuff.empty();
    sendBuff = "AUTH LOGIN\r\n";
    if (false == Send(sendBuff) || false == Recv()) //longin request
    {
        return 1; //1 is because of the internet
    }

    sendBuff.empty();
    int pos = user.find('@', 0);
    sendBuff = user.substr(0, pos); //get user name

    char *ecode;

    ecode = base64Encode(sendBuff.c_str(), strlen(sendBuff.c_str()));
    sendBuff.empty();
    sendBuff = ecode;
    sendBuff += "\r\n";
    delete[]ecode;

    if (false == Send(sendBuff) || false == Recv()) //send user name and get recive
    {
        return 1; //1 is because of the internet
    }

    sendBuff.empty();
    ecode = base64Encode(pass.c_str(), strlen(pass.c_str()));
    sendBuff = ecode;
    sendBuff += "\r\n";
    delete[]ecode;

    if (false == Send(sendBuff) || false == Recv()) //send passport and get recive
    {
        return 1; //1 is because of the internet
    }

    if (NULL != strstr(buff, "550"))
    {
        return 2;//2 is because of the user name
    }

    if (NULL != strstr(buff, "535")) //535 is field
    {
        return 3; //3 is the password wrong
    }
    return 0;
}
//send email head
bool CSmtp::SendEmailHead()
{
    std::string sendBuff;
    sendBuff = "MAIL FROM: <" + user + ">\r\n";
    if (false == Send(sendBuff) || false == Recv())
    {
        return false; // false because the internet
    }

    std::istringstream is(targetAddr);
    std::string tmpadd;
    while(is>>tmpadd)
    {
        sendBuff.empty();
        sendBuff = "RCPT TO: <" + tmpadd + ">\r\n";
        if (false == Send(sendBuff) || false == Recv())
        {
            cout<<"wangluocuowu!!!";
            return false; //false because the internet
        }
    }

    sendBuff.empty();
    sendBuff = "DATA\r\n";
    if (false == Send(sendBuff) || false == Recv())
    {
        cout<<"wangluocuowu!!!";
        return false; //false because the internet
    }

    sendBuff.empty();
    FormatEmailHead(sendBuff);
    if (false == Send(sendBuff))
    {
        return false; //false because the internet
    }
    return true;
}
//init what you want to send
void CSmtp::FormatEmailHead(std::string &email)
{
    email = "From: ";
    email += user;
    email += "\r\n";

    email += "To: ";
    email += targetAddr;
    email += "\r\n";

    email += "Subject: ";
    email += title;
    email += "\r\n";

    email += "MIME-Version: 1.0";
    email += "\r\n";

    email += "Content-Type: multipart/mixed;boundary=qwertyuiop";
    email += "\r\n";
    email += "\r\n";
}

bool CSmtp::SendTextBody()  //send text
{
    std::string sendBuff;
    sendBuff = "--qwertyuiop\r\n";
    sendBuff += "Content-Type: text/plain;";
    sendBuff += "charset=\"gb2312\"\r\n\r\n";
    sendBuff += content;
    sendBuff += "\r\n\r\n";
    return Send(sendBuff);
}

int CSmtp::SendAttachment_Ex() //send file
{
    for (std::list<FILEINFO *>::iterator pIter = listFile.begin(); pIter != listFile.end(); pIter++)
    {
        //cout << "Attachment is sending ~~~~~" << endl;
        //cout << "Please be patient!" << endl;
        std::string sendBuff;
        sendBuff = "--qwertyuiop\r\n";
        sendBuff += "Content-Type: application/octet-stream;\r\n";
        sendBuff += " name=\"";
        sendBuff += (*pIter)->fileName;
        sendBuff += "\"";
        sendBuff += "\r\n";

        sendBuff += "Content-Transfer-Encoding: base64\r\n";
        sendBuff += "Content-Disposition: attachment;\r\n";
        sendBuff += " filename=\"";
        sendBuff += (*pIter)->fileName;
        sendBuff += "\"";

        sendBuff += "\r\n";
        sendBuff += "\r\n";
        Send(sendBuff);
        std::ifstream ifs((*pIter)->filePath, std::ios::in | std::ios::binary);
        if (false == ifs.is_open())
        {
            return 4; //4 is open false
        }
        char fileBuff[MAX_FILE_LEN];
        char *chSendBuff;
        memset(fileBuff, 0, sizeof(fileBuff));
        //use base64 to send
        while (ifs.read(fileBuff, MAX_FILE_LEN))
        {
            //cout << ifs.gcount() << endl;
            chSendBuff = base64Encode(fileBuff, MAX_FILE_LEN);
            chSendBuff[strlen(chSendBuff)] = '\r';
            chSendBuff[strlen(chSendBuff)] = '\n';
            send(sockClient, chSendBuff, strlen(chSendBuff), 0);
            delete[]chSendBuff;
        }
        //cout << ifs.gcount() << endl;
        chSendBuff = base64Encode(fileBuff, ifs.gcount());
        chSendBuff[strlen(chSendBuff)] = '\r';
        chSendBuff[strlen(chSendBuff)] = '\n';
        int err = send(sockClient, chSendBuff, strlen(chSendBuff), 0);

        if (err != strlen(chSendBuff))
        {
            cout << "err to send file!" << endl;
            return 1;
        }
        delete[]chSendBuff;
    }
    return 0;
}

bool CSmtp::SendEnd() //send end
{
    std::string sendBuff;
    sendBuff = "--qwertyuiop--";
    sendBuff += "\r\n.\r\n";
    if (false == Send(sendBuff) || false == Recv())
    {
        return false;
    }
    //cout << buff << endl;
    sendBuff.empty();
    sendBuff = "QUIT\r\n";
    return (Send(sendBuff) && Recv());
}

int CSmtp::SendEmail_Ex()
{
    cout<<"22222";
    if (false == CreateConn())
    {
        cout<<"ss00"<<endl;
        return 1;
    }
    //Recv();
    int err = Login(); //login
    if (err != 0)
    {
        cout<<"ss11"<<endl;
        return err; //retrun err
    }
    cout<<"login succeed!";
    if (false == SendEmailHead()) //send email head
    {
        cout<<"ss22"<<endl;
        return 1; //1 is because of the internet
    }
    cout<<"sendemailhead succeed!";
    if (false == SendTextBody())
    {
        cout<<"ss33"<<endl;
        return 1; //1 is because of the internet
    }
    cout<<"sendemailbody succeed!";
    err = SendAttachment_Ex();
    if (err != 0)
    {
        cout<<"ss44"<<endl;
        return err;
    }
    if (false == SendEnd())
    {
        cout<<"ss55"<<endl;
        return 1; //1 is because of the internet
    }
    cout<<"sendemailend succeed!";
    return 0; //0 is means succeed
}

void CSmtp::AddAttachment(std::string &filePath) //add file
{
    FILEINFO *pFile = new FILEINFO;
    strcpy_s(pFile->filePath, filePath.c_str());
    const char *p = filePath.c_str();
    strcpy_s(pFile->fileName, p + filePath.find_last_of("\\") + 1);
    listFile.push_back(pFile);
}

void CSmtp::DeleteAttachment(std::string &filePath) //delete file
{
    std::list<FILEINFO *>::iterator pIter;
    for (pIter = listFile.begin(); pIter != listFile.end(); pIter++)
    {
        if (strcmp((*pIter)->filePath, filePath.c_str()) == 0)
        {
            FILEINFO *p = *pIter;
            listFile.remove(*pIter);
            delete p;
            break;
        }
    }
}

void CSmtp::DeleteAllAttachment() //delete all file
{
    for (std::list<FILEINFO *>::iterator pIter = listFile.begin(); pIter != listFile.end();)
    {
        FILEINFO *p = *pIter;
        pIter = listFile.erase(pIter);
        delete p;
    }
}

void CSmtp::SetSrvDomain(std::string &domain)
{
    this->domain = domain;
}

void CSmtp::SetUserName(std::string &user)
{
    this->user = user;
}

void CSmtp::SetPass(std::string &pass)
{
    this->pass = pass;
}
void CSmtp::SetTargetEmail(std::string &targetAddr)
{
    this->targetAddr = targetAddr;
}
void CSmtp::SetEmailTitle(std::string &title)
{
    this->title = title;
}
void CSmtp::SetContent(std::string &content)
{
    this->content = content;
}
void CSmtp::SetPort(int port)
{
    this->port = port;
}
