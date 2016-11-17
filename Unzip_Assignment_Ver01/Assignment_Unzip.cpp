#include "Assignment_Unzip.hh"
#include <QDebug>
#include <JlCompress.h>
#include <string.h>
#include <cstdio>
#include <smtp.h>


using namespace std;
/*---------------- reload weapon ready to shoot ---------------------*/
Assignment_Unzip::Assignment_Unzip(int Stu_Index, int file_name_valid,
                                   int file_zip_valid, double Stu_ID,
                                   const char *F_Dir_Origin, const char *current_dir, const char *F_name_Origin[],
                                   int F_number)
                                    {
/*---------------- reload weapon ready to shoot ---------------------*/
    m_Stu_Index = Stu_Index;
    m_file_name_valid = file_name_valid;
    m_file_zip_valid = file_zip_valid;
    m_Stu_ID = Stu_ID;
    m_F_Dir_Origin = F_Dir_Origin;
    m_current_dir = current_dir;
    m_F_number = F_number;
    for(int i = 256; i >= 0; i--)
        m_F_name_Origin[i] = F_name_Origin[i];
    m_file_name_valid = -1;
    m_file_zip_valid = -1;

}
/*------------------------- Check the files ----------------------------
* if flies follow the rule, set corresponding flag in order to let others
* know if there is zipfile existed, unzip it after check its inside content
* NOTICE: Assume that m_F_name_Origin[] save downloaded files name without
* path
-----------------------------------------------------------------------*/

int Assignment_Unzip::A_Check_file(int &f_c_flag, int &f_q_flag,
                                    const char *F_Dir_New){
/*---------------- whether file name follows rule ---------------------*/
    const char *File_CPP = ".cpp";
    const char *File_CC = ".cc";
    const char *File_HH = ".hh";
    const char *File_Zip = ".zip";
    const char *file_name_in_zip[100];                    // the name of files in a zipfile
    int File_in_Index = 0;                                // for files in zipfile
    char *p;
    for(int i = 0; i< m_F_number;i++)                     // m_F_number is how many file student submitted
    {
        p = strrchr(m_F_name_Origin[i], '.');               // m_F_name_Origin[] is their names
        if(!strcmp(p,File_CC) or !strcmp(p,File_CPP) or !strcmp(p,File_HH)
            or !strcmp(p,File_Zip)){                        // strcmp is for comparing two string

            m_file_name_valid = 1;                          // if it is so, set flag 1
            f_c_flag = 1;
            m_file_zip_valid = -1;
            f_q_flag = -1;                                   // we are not sure aboue whether zipfile can be unziped
            cout << f_c_flag << '\n';
        }
        else{
            m_file_name_valid = 0;
            m_file_zip_valid = -1;
            return 0;
        }
    }
/*---------------- unzip files from a zipfile ---------------------
* 1. to determine we do have zipfile;
* 2. if we do, what's inside, who are they, how many are they; if we
*    do not have one, it is no neccessary to run unzip. Instead, deal
*    with next student;
* 3. we have their names and the number of how many. we have
*    to check them, to see whether they follow name rule. if they do,
*    unzip this zipfile. However, we go to deal with next student if
*    zipfile contains file whose name is invalid;
* 4. unzip file, if fail to do that, set stu[i].F_info.file_zip_valid
*    (f_c_flag) 0 indicating this zipfile is broken;
* 5. update data table;
---------------------------------------------------------------------*/
// reach to this step means files in current directory follow the rules
    char *temp_Dir;
    *temp_Dir = '\0';
    for(int i = 0; i< m_F_number;i++)                   // check every file
    {
        p = strrchr(m_F_name_Origin[i], '.');
        if(!strcmp(p,File_Zip)){
            strcat(temp_Dir, m_F_Dir_Origin);
            strcat(temp_Dir, m_F_name_Origin[i]);       // combine filename with directory and ready to unzip
            int count = 0;                              // number of file in a zipfile

            temp_Dir = "/Users/fangmingzhao/course/Project/unziptest.zip";  // for testing
            QStringList F_List = JlCompress::getFileList(temp_Dir);
            if(F_List.count() == 0){                  // nothing in zipfile or cant be unzipped
                    m_file_zip_valid = 0;              // meaning something wrong with zipfile
                    count = -1;
                    return 0;
            }
            count = F_List.count();                     // how many files in zipfile
            foreach (QString item, F_List) {
                    QByteArray p1 = item.toLatin1();
                    if(!strcmp(p1.data(),File_CC) or !strcmp(p1.data(),File_CPP) or !strcmp(p1.data(),File_HH)
                        or !strcmp(p1.data(),File_Zip)){
                        file_name_in_zip[File_in_Index] = p1.data();
                        m_file_name_valid = 1;          // at least this file follows the rule

                    }                                   // by this step, we will how many files in a zip
                else{
                        m_file_name_valid = 0;
                        f_c_flag = m_file_name_valid;
                        m_file_zip_valid = 0;
                        f_q_flag = m_file_zip_valid;
                        count = -1;                     // it doesnt make sense to count items in a zipfile if
                                                        // no valid file in;
                        return 0;
                    }

                }
            QStringList F_Unzip = JlCompress::extractDir(temp_Dir, m_F_Dir_New);    // unzip file
            if(F_Unzip.count() == 0){                  // nothing in zipfile or cant be unzipped
                    m_file_zip_valid = 0;              // meaning something wrong with zipfile
                    return 0;
                }else{
                    m_file_zip_valid = 1;
                    return 1;
            }


        }

    }
    f_c_flag = m_file_name_valid;
    f_q_flag = m_file_zip_valid;
    return 1;
/*---------------- reserved for future ---------------------*/
}
/*---------------- send mail to student whose submitted file are not valid -------------------*/
void Assignment_Unzip::A_Send_mail(int f_c_flag, int f_q_flag, const char *s_mailaddress){

}

#ifdef WIN32
/*send mail function */
//author: He song

//function send()
void Send(SOCKET& s, string& data) {
    if( send(s, data.c_str(), data.length(), 0) == SOCKET_ERROR ) {
        cerr<<"send data \""<<data<<"\" error"<<endl;
    }
}

//function recv()
void Recv(SOCKET& s, char* buf, int len) {
    memset(buf, 0, len);
    if( recv(s, buf, len, 0) == SOCKET_ERROR ) {
        cerr<<"error, while receiving data"<<endl;
    }
}

string Base64Encode(const string& src) {
    int i, j, srcLen = src.length();
    string dst(srcLen / 3 * 4 + 4, 0);
    for(i = 0, j= 0; i <=srcLen - 3; i+=3, j+=4) {
        dst[j] = (src[i] & 0xFC) >> 2;
        dst[j+1] = ((src[i] & 0x03) << 4) + ((src[i+1] & 0xF0) >> 4);
        dst[j+2] = ((src[i+1] & 0x0F) << 2) + ((src[i+2] & 0xC0) >> 6);
        dst[j+3] = src[i+2] & 0x3F;
    }
    if( srcLen % 3 == 1 ) {
        dst[j] = (src[i] & 0xFC) >> 2;
        dst[j+1] = ((src[i] & 0x03) << 4);
        dst[j+2] = 64;
        dst[j+3] = 64;
        j += 4;
    }
    else if( srcLen % 3 == 2 ) {
        dst[j] = (src[i] & 0xFC) >> 2;
        dst[j+1] = ((src[i] & 0x03) << 4) + ((src[i+1] & 0xF0) >> 4);
        dst[j+2] = ((src[i+1] & 0x0F) << 2);
        dst[j+3] = 64;
        j+=4;
    }

    static unsigned char *base64 = (unsigned char*)("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=");
    for(i = 0; i < j; ++i) {    //map 6 bit value to base64 ASCII character
        dst[i] = base64[(int)dst[i]];
    }

    return dst;
}

bool Send_mail(const string& smtpServer, const string& username, const string& pw, const string& to, const string& data) {
    hostent *ph = gethostbyname(smtpServer.c_str());
    if( ph == NULL ) {
        cerr<<"no host: "<<smtpServer<<endl;
        return false;
    }

    sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(25);                                //port of SMTP
    memcpy(&sin.sin_addr.S_un.S_addr, ph->h_addr_list[0], ph->h_length);

    //connect to the mail server
    SOCKET s = socket(PF_INET, SOCK_STREAM, 0);
    if( connect(s, (sockaddr*)&sin, sizeof(sin)) ) {
        cerr<<"failed to connect the mail server"<<endl;
        return false;
    }

    //
    char recvBuffer[1024];
    Recv(s, recvBuffer, sizeof(recvBuffer));    //wait for greeting message
    Send(s, "HELO " + smtpServer + "\r\n");
    Recv(s, recvBuffer, sizeof(recvBuffer));    //should recv "250 OK"

    //start to log in
    Send(s, (string)"auth login\r\n");
    Recv(s, recvBuffer, sizeof(recvBuffer));    //should recv "334 username:"(This is the decode message)

    Send(s, Base64Encode(username) + "\r\n");
    Recv(s, recvBuffer, sizeof(recvBuffer));
    if( string(recvBuffer).substr(0, 3) != "334" ) {
        cout<<"username is error!"<<endl;
        return false;
    }

    Send(s, Base64Encode(pw) + "\r\n");
    Recv(s, recvBuffer, sizeof(recvBuffer));
    if( string(recvBuffer).substr(0, 3) != "235") {
        cout<<"password error"<<endl;
        return false;
    }

    //Set sender
    Send(s, "mail from:<" + username + ">\r\n");
    Recv(s, recvBuffer, sizeof(recvBuffer));    //should recv "250 Mail OK"

    //set receiver
    Send(s, "rcpt to:<" + to + ">\r\n");
    Recv(s, recvBuffer, sizeof(recvBuffer));    //should recv "250 Mail OK"

    //send data
    Send(s, (string)"data\r\n");
    Recv(s, recvBuffer, sizeof(recvBuffer));    //should recv "354 End data with <CR><LF>.<CR><LF>"
    Send(s, "to:" + to + "\r\n" + "subject:the newest IP\r\n\r\n" + data + "\r\n.\r\n");
    Recv(s, recvBuffer, sizeof(recvBuffer));

    Send(s, (string)"quit\r\n");
    Recv(s, recvBuffer, sizeof(recvBuffer));
    closesocket(s);
    return true;
}


/*---------------- send mail to student whose submitted file are not valid -------------------*/




void Assignment_Unzip::A_Send_mail(int f_c_flag, int f_q_flag, const char *s_mailaddress){
    string text[2];
    text[0]="You give a wrong zipfile, you should resend a new zipfile!";
    text[1]="The file you given us not include .cc .cpp or .hh";
	int i;
	if(f_c_flag)
    {
        i=0;	  // I am not sure what the sever it is, so I just add the text and s_mailaddress to the send_mail
    }
    if(f_q_flag)
    {
        i=1;
    }
	CSmtp smtp(
		587,
		"nexus.stevens.edu",
		"stevens_username",
		"password",
		Stu_Mail_Addr,
		"Hello Student"+Stu_ID,
		text[i]
	);
    
#endif
