#include "Assignment_Unzip.hh"
#include <QDebug>
#include <JlCompress.h>
#include <string.h>
#include <cstdio>


using namespace std;
/*
 * int m_Stu_Index, m_file_name_valid, m_file_zip_valid;
const char *m_F_Orname, *m_F_Exname, *m_F_Dir_Origin, *m_F_Dir_New;
const char *m_current_dir;
double m_Stu_ID;
*/
//Assignment_Unzip::Assignment_Unzip(int Stu_Index, const char *F_Orname, const char *F_Exname, const char *F_Dir_Origin, const char *F_Dir_New, const char *current_dir): m_Stu_Index(Stu_Index), m_F_Orname(F_Orname), m_F_Exname(F_Exname), m_F_Dir_Origin(F_Dir_Origin), m_F_Dir_New(F_Dir_New), m_current_dir(current_dir){
/*----------------  ---------------------*/


Assignment_Unzip::Assignment_Unzip(int Stu_Index, int file_name_valid,
                                   int file_zip_valid, double Stu_ID,
                                   const char *F_Dir_Origin, const char *current_dir, const char *F_name_Origin[],
                                   int F_number)
                                    {
/*----------------  ---------------------*/
    m_Stu_Index = Stu_Index;
    m_file_name_valid = file_name_valid;
    m_file_zip_valid = file_zip_valid;
    m_Stu_ID = Stu_ID;
    m_F_Dir_Origin = F_Dir_Origin;
    m_current_dir = current_dir;
    m_F_number = F_number;
    *m_F_name_Origin = *F_name_Origin;

}

int Assignment_Unzip::A_Check_file(int &f_c_flag, int &f_q_flag,
                                    const char *F_Dir_New){
/*--------------- reference -------------------------------------------
    // F_Exname = "hehe";
    // cout << F_Exname;
//   const char *zipfilename=NULL;

//    zipfilename = m_F_Orname;               // pass file name


        if(JlCompress::compressDir(zipfilename, m_F_Dir_Old))
        {
            qDebug() << "Created:" << zipfilename;

        }
        else
        {
            qDebug() << "Could not created:" << zipfilename;
        }
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
/*---------------- unzip files from a zipfile ---------------------*/
// reach to this step means files in current directory follow the rules
    char *temp_Dir;
    for(int i = m_F_number-1; i>=0;i--)
    {
        p = strrchr(m_F_name_Origin[i], '.');
        if(!strcmp(p,File_Zip)){
            strcat(temp_Dir, m_F_Dir_Origin);
            strcat(temp_Dir, m_F_name_Origin[i]);       // combine filename with directory and ready to unzip
            int count = 0;                              // number of file in a zipfile
            char** file_name_zip = NULL;
            char *s;
            temp_Dir = "/Users/fangmingzhao/course/Project/unziptest.zip";
            QStringList F_List = JlCompress::getFileList(temp_Dir);
            foreach (QString item, F_List) {
                    QByteArray p1 = item.toLatin1();
                    file_name_zip[count] = p1.data();

                    count++;
            }
            count++;                                     // by this step, we will how many files in a zip

            // do they follow the name rules???
            // yes set f_q_flag 1, no f_q_flag 0;

            // whether zipfile can be unziped
            /* --- get into zip file and see whether these files are desired
             * QStringList getFileList(QString fileCompressed)
             */
            if(!f_q_flag){
                QStringList F_List = JlCompress::extractDir(temp_Dir, m_F_Dir_New);
            }
            else{
                return 0;
            }
        }



        // put these files into a certain directory, under central directory
    }

/*---------------- check these unzip files again, to see whether they follow rules ---------------------*/

/*---------------- reserved for future ---------------------*/

    for(int i = m_F_number-1; i>=0;i--){

        QStringList F_List = JlCompress::extractDir(m_F_Dir_Origin, m_F_Dir_New);      // here is suppose to have a flag to indicate whether unzipping a file is finished or ok.
    }
}

void Assignment_Unzip::A_Send_mail(int f_c_flag, int f_q_flag, const char *s_mailaddress){

}
