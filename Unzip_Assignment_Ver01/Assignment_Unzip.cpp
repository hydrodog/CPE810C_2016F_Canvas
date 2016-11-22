#include "Assignment_Unzip.hh"
#include <QDebug>
#include <JlCompress.h>
#include <string.h>
#include <cstdio>



using namespace std;
/*---------------- reload weapon ready to shoot ---------------------*/
Assignment_Unzip::Assignment_Unzip(int Stu_Index, int file_name_valid,
                                   int file_zip_valid, double Stu_ID,
                                   const char *F_Dir_Origin, const char *current_dir, const char *F_name_Origin[],
                                   int F_number, int file_rule_num, const char *file_name_rule_M[],
                                   const char *file_name_rule_E[])
                                    {
/*---------------- reload weapon ready to shoot ---------------------*/
    m_Stu_Index = Stu_Index;
    m_file_name_valid = file_name_valid;
    m_file_zip_valid = file_zip_valid;
    m_Stu_ID = Stu_ID;
    m_F_Dir_Origin = F_Dir_Origin;
    m_current_dir = current_dir;
    m_F_number = F_number;
    for(int i = 0; i < 100; i++)
        m_F_name_Origin[i] = F_name_Origin[i];
    m_file_name_valid = -1;
    m_file_zip_valid = -1;
//    m_file_name_rule_M = new const char*[file_rule_num];
//    m_file_name_rule_E = new const char*[file_rule_num];
    for(int i = 0; i < file_rule_num; i++){
        m_file_name_rule_M[i] = file_name_rule_M[i];
        m_file_name_rule_E[i] = file_name_rule_E[i];
    }
    m_file_rule_num = file_rule_num;
//    delete[] m_file_name_rule_E;
//    delete[] m_file_name_rule_M;
}
/*------------------------- Check the files ----------------------------
* if flies follow the rule, set corresponding flag in order to let others
* know if there is zipfile existed, unzip it after check its inside content
* NOTICE: Assume that m_F_name_Origin[] save downloaded files name without
* path
* NOTICE: the number of files each student submit should not be more than
* 20. In order to pervent that thing happened, a related method should be
* written.
-----------------------------------------------------------------------*/

int Assignment_Unzip::A_Check_file(int &f_c_flag, int &f_q_flag, const char *file_name_qualified[]){
/*---------------- whether file name follows rule ---------------------*/
    int file_qname_index = 0, loop_count1, loop_count2 = 0;      // for files in zipfile
    int file_inzip_num = 0;                              // number of file in a zipfile
    const char *p, *q = "*";

    char *full_name;

    for(int i = 0; i< m_F_number;i++)                     // m_F_number is how many file student submitted
    {                                                     // m_F_name_Origin[] is their names
        loop_count1 = 0;
        p = strrchr(m_F_name_Origin[i], '.');             // p is extra name;
        for(int j=0; j<m_file_rule_num; j++){
            if(strcmp(m_file_name_rule_M[j],q)){                   // one certain file name, including its extra
                                                                   // name must be the same to name rule descript
                full_name = (char*)malloc(strlen(m_file_name_rule_M[j])+strlen(m_file_name_rule_E[j])+1);

                *full_name = NULL;
                strcpy(full_name, m_file_name_rule_M[j]);
                strcat(full_name, m_file_name_rule_E[j]);
                if(strcmp(full_name,m_F_name_Origin[i])!=0){
                    loop_count1++;                                   // if full name does not equal to orignal name
                    loop_count2++;                                                // loop count++
                }
            }else{
                if(strcmp(m_file_name_rule_E[j], p)!=0 && strcmp(p, ".zip") !=0){   // main name equal to *,
                                                                                // meaning main name does
                    loop_count1++;
                    loop_count2++;
                }
            }
        }
        if(loop_count1 < m_file_rule_num && strcmp(p, ".zip") !=0){         // store file name who is qualified, except
                                                                            // zipfile. Because automation group can do
                                                                            // nothing to zipfiles before these zipfiles
                                                                            // are unzipped
            file_name_qualified[file_qname_index] = (char*)malloc(strlen(m_F_name_Origin[i])+1);    // it is ok?
            file_name_qualified[file_qname_index] = m_F_name_Origin[i];
            cout << file_name_qualified[file_qname_index];
            file_qname_index++;
        }

    }
 /*-------- reserved for passing reference, m_file_name_qualified and file_qname_index --------*/
    if(loop_count2 == m_F_number*2){
        f_c_flag = 0;f_q_flag = 0;                      // if loop_count2 equals to 2 times number of files each
                                                        // student submit, these files are not desired ones.
        return 0;
    }
    f_c_flag = 1;f_q_flag = -1;
/*---------------- unzip files from a zipfile ---------------------
* 1. determine we do have zipfile;
* 2. if we do, what's inside, who are they, how many are they; if we
*    do not have one, it is unneccessary to run unzip. Instead, go
*    to next student;
* 3. we have files names and the number of how many. we have
*    to check them, to see whether they follow name rule. if they do,
*    unzip this zipfile. However, we go to next student if
*    zipfile contains file whose name is invalid;
* 4. unzip file, if fail to do that, set stu[i].F_info.file_zip_valid
*    (f_c_flag) 0 indicating this zipfile is broken;
* 5. update data table;
---------------------------------------------------------------------*/
// reach to this step means files in current directory follow the rules
    loop_count2 = 0;
    char *temp_Dir;
    for(int i = 0; i< m_F_number;i++)                   // check every file
    {
        p = strrchr(m_F_name_Origin[i], '.');
        if(!strcmp(p,".zip")){
            temp_Dir = (char*)malloc(strlen(m_F_Dir_Origin)+strlen(m_F_name_Origin[i])+1);  // allocate memory
            *temp_Dir = NULL;
            strcat(temp_Dir, m_F_Dir_Origin);
            strcat(temp_Dir, m_F_name_Origin[i]);       // combine filename with directory and ready to unzip
            temp_Dir = "/Users/fangmingzhao/course/Project/unziptest.zip";  // for testing
            QStringList F_List = JlCompress::getFileList(temp_Dir);
            if(F_List.count() == 0){                  // nothing in zipfile or cant be unzipped
                    f_q_flag = 0;                     // meaning something wrong with zipfile
                    file_inzip_num = -1;
                    return 0;
            }
            file_inzip_num = F_List.count();                     // how many files in zipfile
            foreach (QString item, F_List) {
                loop_count1 = 0;
                QByteArray p1 = item.toLatin1();
                for(int i=0; i<m_file_rule_num; i++){                      // number of rules
                    if(strcmp(m_file_name_rule_M[i],q)){                   // one certain file name, including its extra
                                                                           // name must be the same to name rule descript
                        *full_name = NULL;
                        strcpy(full_name, m_file_name_rule_M[i]);
                        strcat(full_name, m_file_name_rule_E[i]);
                        if(strcmp(full_name,p1.data())!=0){
                            loop_count1++;                                   // if full name does not equal to orignal name
                            loop_count2++;                                                // loop count++
                        }
                    }else{
                        if(strcmp(m_file_name_rule_E[i], strrchr(p1.data(), '.'))!=0){   // main name equal to *,
                                                                                        // meaning main name does
                            loop_count1++;
                            loop_count2++;
                        }
                    }

                }
                if(loop_count1 < m_file_rule_num){
                    file_name_qualified[file_qname_index] = (char*)malloc(strlen(p1.data())+1);
                    file_name_qualified[file_qname_index] = p1.data();
                    file_qname_index++;
                }
            }
            if(loop_count2 == file_inzip_num*2){
                f_c_flag = 0;f_q_flag = 1;                      // if loop_count2 equals to 2 times number of files each
                                                                // student submit, these files are not desired ones though
                                                                // zipfile can be unzipped
                return 0;
            }
            QStringList F_Unzip = JlCompress::extractDir(temp_Dir, m_F_Dir_New);    // unzip file
            if(F_Unzip.count() == 0){                  // nothing in zipfile or cant be unzipped
                    f_q_flag = 0;                      // meaning something wrong with zipfile
                    return 0;
                }else{
                    f_q_flag = 1;
                    return 1;
            }
        }

    }

    return 1;
/*---------------- reserved for future ---------------------*/
}
void Assignment_Unzip::test(){

    cout << m_file_name_rule_E[0];
}

/*---------------- send mail to student whose submitted file are not valid -------------------*/
void Assignment_Unzip::A_Send_mail(int f_c_flag, int f_q_flag){
    if(f_c_flag)
        f_c_flag = 1;
    if(f_q_flag)
        f_q_flag = 1;
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
    if(f_c_flag)
    {
        Send_mail(s_mailaddress,text[0], );	  // I am not sure what the sever it is, so I just add the text and s_mailaddress to the send_mail
    }
    if(f_q_flag)
    {
        Send_mail(s_mailaddress,text[1]);
    }
#endif
