#ifndef ZIPFILE_H
#define ZIPFILE_H

#include "smtp.h"
#include <iostream>
#include <string>
#include <time.h>
#include <unzip.h>
#include <cstdio>
#include <vector>

/**********************************************************
 * author : Fangming Zhao, Zheao Ma
 * working OS: Windows 7
 * IDE: Qt Creator 4.1.0
 * tool: C++
 * group: C/zip file rules
 * group member: Zheao Ma, He Song, Yuan Zhou
 *
 * program ver: v1.00
 *
 ***********************************************************/


static char current_pro_dir[256];             // current directory this program stay
static int Get_dir_OK;                        // 0 fail to get directory of pro



/*------------ declare public data area for each group in project to add modify and maintain ------------*/

#ifndef _STUDENT                                    // struct for course including three structs: student
                                                    // information, assignment information, file(assignment itself) information
typedef struct{




    #ifndef _STUDENT_INFO

    typedef struct{
        int Stu_Index;                              // index for retrieving information of student
        int Stu_Assigment_Grade_Current;            // grade students will get from this assignment
        int Stu_Assigment_Grade_Min;                // the minimum grade that students can get
        int Stu_Assigment_Grade_Max;                // the maximum grade that students can get
        double Stu_ID;                              // the ID number of student
        const char *Stu_Name;                             // student's name which has to be english

    }Student_info;                                     // stu_info stores student information

    #define _STUDENT_INFO
    #endif

    #ifndef _FILE_INFO

    typedef struct {
        const char *File_name_Origin[256];               // files's name
        const char *File_name_Main;
        const char *File_name_Extra;                  // file's extra name
                                                           // name if download group do not tell

        const char  *File_dir_Origin, *File_dir_N;         // position that file is located and the position where
        std::vector<std::string> File_dir_N_new;
                                                           // the copies of files and unzip files are?? we are going to store these new files under the same level where orignal files are sitting
        const char *File_Extname_N;                 // give something if u dont do anything
        const char *file_unzip_dir;                 // directory that unzipped files put into; the name is
                                                    // combination of Stu_ID and Stu_Index
        const char *file_name_inzip[20];            // file names in a zipfile;
        const char *file_name_qualified[30];

        int file_number;                            // how many files student submit
        int file_dir_err;                           // tell us whether certain file has vaild path
        int file_name_err;                          // tell us whether certain file has vaild name
        int file_name_valid;                        // whether file name is valid, if its not, it is unneccessary
                                                    // to compile file, meaning program should jump to next student
                                                    // to deal with assignment
        int file_zip_valid;                         // whether zipfile can be unzipped, if not,it is unneccessary
                                                    // to compile file,meaning program should jump to next student
                                                    // to deal with assignment

                                                    // before unzipping file, we have to list files (by using
                                                    // listgetFileList(QString fileCompressed))
                                                    // and see whether these files follow name rule. If they dont,
                                                    // set file_name_valid to 0 and file_zip_valid 1
    } File_info;                                         // stores file (download from canvas, actually they are assignments) information. There are some seats reserved for class unzip, for now, we are not sure.

    #define _FILE_INFO
    #endif

    #ifndef _ASSIGNMENT_INFO

    typedef struct {

        const char *Assigment_Comment;                // grader's comment to a assignment
        const char *Assignment_Graph_Title;
        const char *Assignment_Title;           //
    } Assignment_info;                          // all the things about assignment
    #define _ASSIGNMENT
    #endif
    Student_info S_info;
    File_info F_info;
    Assignment_info A_info;

} Student;                                   // Assigment_information is to store all information about assigment like

#define _STUDENT
#endif

#ifndef _HOMEWORK

struct HomeWork{                            // Here is my idea, suppose there is texteditor on GUI, grader put
                                            // rule of name of assignment like, he wants main.cc and *.cpp
                                            // and he uses ";" to divid these two rules. Like main.cc;*.cpp
                                            // our job is to seperate the rule and put them into the following
                                            // array of char. For example: main.cc is divided into two parts, one
                                            // is "main" and put into const char *File_name_rule_Main[0]. The other
                                            // one is ".cc" and put into const char *File_name_rule_Extra[0];
                                            // Meaning the rule0 requests file name is consisted with two parts,
                                            // "main" and ".cc". Also you have rule1 which requests file name must
                                            // must be consisted with ".cpp" no matter what's inside of File_name_
                                            // rule_Main[1];

    const char *File_name_rule_Main[15];    // main name of assignment grader wants; come from outside and given by
                                            // grader;
    const char *File_name_rule_Extra[15];       // main name of assignment grader wants; come from outside and given by
                                            // grader;
    int rule_num;                           // how many rules; we may not use this guy; BE AWARED: number of rules
                                            // should not be more than 15.
};

#define _HOMEWORK
#endif

//---------------------------------------------------------------------------------

class Assignment_Unzip{
private:
    int m_Stu_Index, m_file_name_valid, m_file_zip_valid, m_F_number, m_file_rule_num;
    const char *m_F_Exname, *m_F_Dir_Origin, *m_F_Dir_New;
    const char *m_F_name_Origin[100];
    const char *m_current_dir;
    const char *m_file_name_rule_M[15];
    const char *m_file_name_rule_E[15];
    double m_Stu_ID;
public:                                         // there are two methods;
/* **********************************************************************************
 * Using Stu_Index and Stu_ID to name the directory of each submited assignment;
 * file_name_valid indicates whether submitted file name follows rule, 1 is valid;
 * file_zip_valid indicates whether submitted zipfile can be unzipped, 1 is valid;
 * F_Dir_Origin is where download group put submitted assignment;
 * current_dir is where progame stay;
 * the function of this conductor is like reloading your weapon and prepare to shoot;
 * **********************************************************************************/

    Assignment_Unzip(int Stu_Index, int file_name_valid,
                     int file_zip_valid, double Stu_ID,
                     const char *F_Dir_Origin, const char *current_dir,
                     const char *F_name_Origin[], int F_number, int file_rule_num,
                     const char *file_name_rule_M[],
                     const char *file_name_rule_E[]);



/*------------------ method 1 check file and unzip them if they are valid ----------------*/
    int A_Check_file(int &f_c_flag, int &f_q_flag, const char *file_name_qualified[]);       // check the file to see whether
                                                   // its name follows the rule and
                                                   // can or not be complied if file
                                                   // name is qualified
/*------------------ method 2 send mail to student if their assignment are invalid ----------------*/
    void A_Send_mail();
    void test();

};

#endif // ZIPFILE_H
