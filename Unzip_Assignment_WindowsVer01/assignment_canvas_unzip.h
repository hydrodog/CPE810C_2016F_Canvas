#ifndef ASSIGNMENT_CANVAS_UNZIP_H
#define ASSIGNMENT_CANVAS_UNZIP_H

#include <iostream>

/**********************************************************
 * Author : Zheao Ma
 * OS: Windows 7
 * IDE: Qt Creator 4.1.0
 * Tool: C++
 * Group: C/zip file rules
 * Group member: Fangming Zhao, He Song, Yuan Zhou
 *
 * Program ver: v0.5
 *
 ***********************************************************/

static char current_pro_dir[256];             // current directory this program stay, download group should provide
static int Get_dir_OK;                        // 0 fail to get directory of pro



//------------ declare public area for data downloaded from canvas--------

#ifndef _COURSE_INFO                                // struct for course including three structs: student info
                                                    // assignment info and file(HW uploaded) info
typedef struct{

    #ifndef _STU_INFO

    typedef struct{
        int Stu_Index;                              // index for retrieving information of student
        int Stu_Assigment_Grade_Current;            // grade students will get from this assignment
        int Stu_Assigment_Grade_Min;                // the minimum grade that students can get
        int Stu_Assigment_Grade_Max;                // the maximum grade that students can get
        double Stu_ID;                              // CWID of student
        const char *Stu_Name;                       // student's name
        const char *Stu_Mail_Addr;                  // student's email address
    } Stu_info;

    #define _STU_INFO
    #endif



    #ifndef _FILE_INFO

    typedef struct {
        const char *Filename_Origin[256];           // filename
        const char *Filename_Ext;                   // filename extension

        const char  *File_Dir_Origin, *File_Dir_New;       // directory

        // const char *File_Extname_N;

        int file_number;                            // number of files student submit
        int file_dir_err;                           // tell us whether certain file has vaild path
        // int file_name_err;
        int file_name_valid;                        // whether file name is valid
        int file_zip_valid;                         // whether zipfile can be unzipped


    } File_info;

    #define _FILE_INFO
    #endif



    #ifndef _ASSIGNMENT_INFO

    typedef struct {

        const char *Assigment_Comment;              // comments to the assignment
        const char *Assignment_Graph_Title;
        const char *Assignment_Title;
    } Assignment_info;                              // all the info about assignment
    #define _ASSIGNMENT_INFO
    #endif

    Stu_info S_info;
    File_info F_info;
    Assignment_info A_info;

} Course_info;

#define _COURSE_INFO
#endif

class Assignment_Canvas_Unzip
{
private:
    int m_Stu_Index, m_file_name_valid, m_file_zip_valid, m_file_number;
    const char *m_Filename_Ext, *m_File_Dir_Origin, *m_File_Dir_New;
    const char *m_Filename_Origin[256];
    const char *m_current_dir;
    double m_Stu_ID;
public:
    Assignment_Canvas_Unzip(int Stu_Index, int file_name_valid,
                            int file_zip_valid, double Stu_ID,
                            const char *File_Dir_Origin, const char *current_dir,
                            const char *Filename_Origin[], int file_number, const char *Stu_Mail_Addr);

/*------------------ Check file rules and unzip if possible ----------------*/

    int A_Check_file(int &m_file_name_valid, int &m_file_zip_valid,
                      const char *m_File_Dir_New);

/*------------------ Send mail to students if they fail to follow the file rules ----------------*/

    int A_Send_mail(int m_file_name_valid, int m_file_zip_valid, const char *m_Stu_Mail_Addr);

#endif // ASSIGNMENT_CANVAS_UNZIP_H
