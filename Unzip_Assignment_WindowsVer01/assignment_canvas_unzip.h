#ifndef ASSIGNMENT_CANVAS_UNZIP_H
#define ASSIGNMENT_CANVAS_UNZIP_H

#include <iostream>
#include <cstring>

static char current_pro_dir[256];             // current directory this program stay, download group should provide
static int Get_dir_OK;                        // 0 fail to get directory of pro



//------------ declare public area for data downloaded from canvas--------

#ifndef _COURSE_INFO                                // struct for course including three structs: student info
                                                    // assignment info and file(HW uploaded) info
typedef struct{

    #ifndef _STU_INFO

    typedef struct{
        int Stu_Index;                              // index for retrieving information of student
        int Stu_Assigment_Grade_Current;            // ? grade students will get from this assignment
        int Stu_Assigment_Grade_Min;                // ? the minimum grade that students can get
        int Stu_Assigment_Grade_Max;                // ? the maximum grade that students can get
        long Stu_ID;                                // CWID of student
        const char *Stu_Name;                       // student's name
        const char *Stu_Mail_Addr;                  // student's email address
    } Stu_info;

    #define _STU_INFO
    #endif



    #ifndef _FILE_INFO

    typedef struct {
        const char *Filename_Origin[256];           // filename
        const char *Filename_Ext;                   // filename extension
                                                           // name if download group do not tell
        const char  *File_dir_Origin, *File_dir_N;         // position that file is located and the position where
                                                           // the copies of files and unzip files are?? we are going to store these new files under the same level where orignal files are sitting
        //const char *File_Extname_N;                 // give something if u dont do anything

        int file_number;                            // number of files student submit
        int file_dir_err;                           // tell us whether certain file has vaild path
        int file_name_err;                          // ? tell us whether certain file has vaild name
        int file_name_valid;                        // ? whether file name is valid
        int file_zip_valid;                         // whether zipfile can be unzipped
                                                    // before unzipping file, we have to list files (by using
                                                    // listgetFileList(QString fileCompressed))
                                                    // and see whether these files follow name rule. If they dont,
                                                    // set file_name_valid to 0 and file_zip_valid 1


    } File_info;                                    // stores file (download from canvas, actually they are assignments) information. There are some seats reserved for class unzip, for now, we are not sure.

    #define _FILE_INFO
    #endif



    #ifndef _ASSIGNMENT_INFO

    typedef struct {

        const char *Assigment_Comment;              // grader's comments to the assignment
        const char *Assignment_Graph_Title;
        const char *Assignment_Title;
    } Assignment_info;                              // all the info about assignment
    #define _ASSIGNMENT_INFO
    #endif

    Stu_info S_info;
    File_info F_info;
    Assignment_info A_info;

} Course_info;                                   // Assigment_information is to store all information about assigment like

#define _COURSE_INFO
#endif

class Assignment_Canvas_Unzip
{
private:
    int m_Stu_Index, m_file_name_valid, m_file_zip_valid, m_F_number;
    const char *m_F_Exname, *m_F_Dir_Origin, *m_F_Dir_New;
    const char *m_F_name_Origin[256];
    const char *m_current_dir;
    double m_Stu_ID;
public:
    Assignment_Canvas_Unzip(int Stu_Index, int file_name_valid,
                            int file_zip_valid, double Stu_ID,
                            const char *F_Dir_Origin, const char *current_dir,
                            const char *F_name_Origin, int F_number);
    int A_Check_file(int &f_c_flag, int &f_q_flag,
                     const char *m_F_Dir_New);       // check the file to see whether
                                                       // its name follows the rule and
                                                       // can or not be complied if file
                                                       // name is qualified
    void A_Send_mail(int f_c_flag, int f_q_flag, char const *s_mailaddress);      // notify student whose submitted assigment is not qualified
};

#endif // ASSIGNMENT_CANVAS_UNZIP_H
