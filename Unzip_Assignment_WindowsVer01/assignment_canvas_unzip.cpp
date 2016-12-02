#include "Assignment_Canvas_Unzip.h"
#include <QDebug>
#include <QStringList>
#include <QByteArray>
#include <JlCompress.h>
#include <cstring>
using namespace std;

Assignment_Unzip::Assignment_Unzip(int Stu_Index, int file_name_valid,
                                   int file_zip_valid, double Stu_ID,
                                   const char *File_Dir_Origin, const char *current_dir,
                                   const char *Filename_Origin[], int file_number, const char *Stu_Mail_Addr) : m_Stu_Index(Stu_Index),
                                   m_file_name_valid(file_name_valid), m_file_zip_valid(file_zip_valid), m_Stu_ID(Stu_ID),
                                   m_File_Dir_Origin(File_Dir_Origin), m_current_dir(current_dir), m_Filename_Origin(Filename_Origin),
                                   m_file_number(file_number), m_Stu_Mail_Addr(Stu_Mail_Addr) {}

int Assignment_Unzip::A_Check_file(int &m_file_name_valid, int &m_file_zip_valid,
                                    const char *m_File_Dir_New){

/*---------------- whether file name follows the rules ---------------------*/
    const char *File_CPP = ".cpp";
    const char *File_CC = ".cc";
    const char *File_H = ".h";
    const char *File_Zip = ".zip";

    char *p;
    for(int i = m_file_number-1; i>=0; i--)
    {
        p = strrchr(m_Filename_Origin[i], '.');
        if(!strcmp(p,File_CC) || !strcmp(p,File_CPP) || !strcmp(p,File_H) || !strcmp(p,File_Zip)){
            m_file_name_valid = 1;
        }
        else{
            m_file_name_valid = 0;
            m_file_zip_valid = 1;
            return 0;
        }
    }
/*---------------- unzip files ----------------*/
    char *temp_Dir;
    *temp_Dir = '\0';
    for(int i = m_file_number-1; i>=0; i--)
    {
        p = strrchr(m_Filename_Origin[i], '.');
        if(!strcmp(p,File_Zip)){
            strcat(temp_Dir, m_File_Dir_Origin);
            strcat(temp_Dir, m_Filename_Origin[i]);
            int count = 0;                                // number of files in a zipfile
            // const char* file_name_zip[100];
            // char *s;
            // temp_Dir = "/Users/.../*.zip";
            QStringList File_List = getFileList(temp_Dir);
            if(File_List.count() == NULL)
            {   m_file_zip_valid = 0;
                return 0;
            }
            foreach (QString item, File_List) {
                QByteArray p1 = item.toLatin1();
                if(!strcmp(p1.data(),File_CC) || !strcmp(p1.data(),File_CPP) || !strcmp(p1.data(),File_H))
                { //Declare that no zip files allowed in a zip file
                    m_file_name_valid = 1;
                    count++;
                }
                else
                {   m_file_name_valid = 0;
                    // m_file_zip_valid = 0;
                    return 0;
                }
            }
            QstringList File_Unzip = extractDir(temp_Dir, m_File_Dir_New);
            /*  if(File_List == NULL){
                    m_file_zip_valid = 0;
                    return 0;
                }
            */
                m_file_zip_valid = 1;
                return 0;
        }
    }
}

void Assignment_Unzip::A_Send_mail(int m_file_name_valid, int m_file_zip_valid, const char *m_Stu_Mail_Addr){
    string text[2];
    text[0]="Illegal file! or Your zip file contains illegal files! Please reupload your assignment!";
    text[1]="Fail to unzip your file! Please reupload your assignment!";
    if(m_file_name_valid == 0)
    {   Send_mail(m_Stu_Mail_Addr,text[0]);
    }
    else if(m_file_zip_valid == 0)
    {   Send_mail(m_Stu_Mail_Addr,text[1]);
    }

}
