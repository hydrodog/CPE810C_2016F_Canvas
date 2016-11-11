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

}
/*------------------------- Check the files ----------------------------
* if flies follow the rule, set corresponding flag in order to let others
* know if there is zipfile existed, unzip it after check its inside content
*
-----------------------------------------------------------------------*/

int Assignment_Unzip::A_Check_file(int &f_c_flag, int &f_q_flag,
                                    const char *F_Dir_New){
/*---------------- whether file name follows rule ---------------------*/
    const char *File_CPP = ".cpp";
    const char *File_CC = ".cc";
    const char *File_HH = ".hh";
    const char *File_Zip = ".zip";

    char *p;
    for(int i = m_F_number-1; i>=0;i--)
    {
        p = strrchr(m_F_name_Origin[i], '.');
        if(!strcmp(p,File_CC) or !strcmp(p,File_CPP) or !strcmp(p,File_HH)
            or !strcmp(p,File_Zip)){ // strcmp is for comparing two string

            m_file_name_valid = 1;                          // if it is so, set flag 1
            f_c_flag = 1;
            f_q_flag = -1;                                   // we are not sure aboue whether zipfile can be unziped
            cout << f_c_flag << '\n';
        }
        else{
            m_file_name_valid = 0;
            f_c_flag = 0;
            f_q_flag = -1;
            return 0;
        }
    }
/*---------------- unzip files from a zipfile ---------------------
* 1. to determine we do have zipfile;
* 2. if we do, what's inside, who are they, how many are they, if we
*    do not have, it is no neccessary to run unzip. Instead deal with
*    next student;
* 3. we have their identification and the number of how many. we have
*    to check them to see whether they follow name rule. if they do,
*    unzip this zipfile let me come out. However, we go to deal with
*    next student if zipfile contain invalid name file;
* 4. unzip file, if fail to do that, set stu[i].F_info.file_zip_valid
*    (f_c_flag) 0 indicating this zipfile is broken;
* 5. update data table;
---------------------------------------------------------------------*/
// reach to this step means files in current directory follow the rules
    char *temp_Dir;
    *temp_Dir = '\0';
    for(int i = 0; i<m_F_number;i++)
    {
        p = strrchr(m_F_name_Origin[i], '.');
        if(!strcmp(p,File_Zip)){
            strcat(temp_Dir, m_F_Dir_Origin);

            strcat(temp_Dir, m_F_name_Origin[i]);       // combine filename with directory and ready to unzip
            int count = 0;                              // number of file in a zipfile
            const char *file_name_zip[100];
            char *s;
            temp_Dir = "/Users/fangmingzhao/course/Project/unziptest.zip";  // for testing
            QStringList F_List = JlCompress::getFileList(temp_Dir);
            foreach (QString item, F_List) {
                    QByteArray p1 = item.toLatin1();
                    if(!strcmp(p1.data(),File_CC) or !strcmp(p1.data(),File_CPP) or !strcmp(p1.data(),File_HH)
                        or !strcmp(p1.data(),File_Zip)){
                    f_c_flag = 1;                   // at least this file follows the rule
                    count++;                        // by this step, we will how many files in a zip
                }else{
                        f_c_flag = 0;
                        count = -1;
                        return 0;
                    }

            }

            if(f_c_flag){
                QStringList F_List = JlCompress::extractDir(temp_Dir, m_F_Dir_New);
                //if(F_List == NULL){               // still working on this part
                 //   f_q_flag = 0;
                 //   return 0;
                //}
                f_q_flag = 1;
            }
            else{
                return 0;
            }
        }

    }
/*---------------- reserved for future ---------------------*/
}
/*---------------- send mail to student whose submitted file are not valid -------------------*/
void Assignment_Unzip::A_Send_mail(int f_c_flag, int f_q_flag, const char *s_mailaddress){

}
