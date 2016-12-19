#include "stdlib.h"
#include "smtp.h"
#include <iostream>
#include <winsock2.h>
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
    hostent *pHostent = gethostbyname(domain.c_str());
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);    //port of SMTP
    memcpy(&sin.sin_addr.S_un.S_addr, pHostent->h_addr_list[0], pHostent->h_length);
    sockClient = socket(AF_INET, SOCK_STREAM, 0); //set socket
    //sockClient;
    if( connect(sockClient, (sockaddr*)&sin, sizeof(sin)) )
    {
        cerr<<"failed to connect the mail server"<<endl;
        return false;
    }
    cout<<"connect succeed"<<endl;
    return true;
}

bool CSmtp::Send(std::string &message)
{
    int err = send(sockClient, message.c_str(), message.length(), 0);
    if (err == SOCKET_ERROR)
    {
        cout<<"Send_Err"<<endl;
        return false;
    }
    return true;
}

bool CSmtp::Recv()
{
    memset(buff, 0, sizeof(char)* (MAXLEN + 1));
    int err = recv(sockClient, buff, MAXLEN, 0); //recive data
    cout<<'+'<<buff<<'+';
    if (err == SOCKET_ERROR)
    {
        return false;
    }
    buff[err] = '\0';
    return true;
}

int CSmtp::Login()
{
    std::string sendBuff;
    sendBuff = "HELO ";
    sendBuff += user; // this part need to use telnet decate
    sendBuff += "\r\n";
    if (false == Send(sendBuff) || false == Recv()) //send and recive
    {
        cout<<"send_err_1";
        return 1; //1 is because of the internet
    }
    sendBuff.empty();
    sendBuff = "AUTH LOGIN\r\n";
    if (false == Send(sendBuff) || false == Recv()) //longin request
    {
        cout<<"send_err_2";
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
    sendBuff = "MAIL FROM: <" + user + ">\n";
    cout<<sendBuff;
    if (false == Send(sendBuff) || false == Recv())
    {
        cout<<"s_head_err1";
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
            cout<<"s_head_err2";
            return false; //false because the internet
        }
    }

    sendBuff.empty();
    sendBuff = "DATA\r\n";
    if (false == Send(sendBuff) || false == Recv())
    {
        cout<<"s_head_err3";
        return false; //false because the internet
    }

    sendBuff.empty();
    FormatEmailHead(sendBuff);
    if (false == Send(sendBuff))
    {
        cout<<"s_head_err4";
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
        cout << "Attachment is sending ~~~~~" << endl;
        cout << "Please be patient!" << endl;
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
    sendBuff.empty();
    sendBuff = "QUIT\r\n";
    return (Send(sendBuff) && Recv());
}

int CSmtp::SendEmail_Ex()
{
    if (false == CreateConn())
    {
        cout<<"conn_err"<<endl;
        return 1;
    }
    int err = Login(); //login
    if (err != 0)
    {
        cout<<"Login_err"<<endl;
        return err; //retrun err
    }
    cout<<"login succeed!"<<endl;
    if (false == SendEmailHead()) //send email head
    {
        cout<<"SendHead_err"<<endl;
        return 1; //1 is because of the internet
    }
    cout<<"SendHead_Succeed!";
    if (false == SendTextBody())
    {
        cout<<"SendBody_err"<<endl;
        return 1; //1 is because of the internet
    }
    cout<<"sendemailbody succeed!";
    err = SendAttachment_Ex();
    if (err != 0)
    {
        cout<<"SendAttachment_err"<<endl;
        return err;
    }
    if (false == SendEnd())
    {
        cout<<"SendEnd_err"<<endl;
        return 1; //1 is because of the internet
    }
    cout<<"SendEnd succeed!"<<endl;
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
