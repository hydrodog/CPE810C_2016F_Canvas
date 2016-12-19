#ifndef __SMTP_H__
#define __SMTP_H__

#include <list>
#include <winsock2.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

const int MAXLEN = 1024;
const int MAX_FILE_LEN = 6000;

static const char base64Char[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

struct FILEINFO
{
    char fileName[128]; //file name
    char filePath[256]; //file path
};

class CSmtp
{
public:
    CSmtp(void);
    CSmtp(
        int port,
        std::string srvDomain,
        std::string userName,
        std::string password,
        std::string targetEmail,
        std::string emailTitle,
        std::string content
        );
public:
    ~CSmtp(void);
public:
    int port;
public:
    std::string domain;
    std::string user;
    std::string pass;
    std::string targetAddr;
    std::string title;
    std::string content;
    std::list <FILEINFO *> listFile;

public:
    char buff[MAXLEN + 1];
    int buffLen;
    SOCKET sockClient;
public:
    bool CreateConn();

    bool Send(std::string &message);
    bool Recv();

    void FormatEmailHead(std::string &email);//format email head
    int Login();
    bool SendEmailHead();
    bool SendTextBody();
    //bool SendAttachment();        //send attachment
    int SendAttachment_Ex();
    bool SendEnd();
public:
    void AddAttachment(std::string &filePath);
    void DeleteAttachment(std::string &filePath);
    void DeleteAllAttachment();

    void SetSrvDomain(std::string &domain);
    void SetUserName(std::string &user);
    void SetPass(std::string &pass);
    void SetTargetEmail(std::string &targetAddr);
    void SetEmailTitle(std::string &title);
    void SetContent(std::string &content);
    void SetPort(int port);
    int SendEmail_Ex();

    char* base64Encode(char const* origSigned, unsigned origLength);
};

#endif // !__SMTP_H__
