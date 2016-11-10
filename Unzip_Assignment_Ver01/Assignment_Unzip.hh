#ifndef ASSIGNMENT_UNZIP_H
#define ASSIGNMENT_UNZIP_H

#include <iostream>
#include <string>
#include <unzip.h>
#include <time.h>
#include <cstdio>




static char current_pro_dir[256];             // current directory this program stay, download group should provide
static int Get_dir_OK;                        // 0 fail to get directory of pro



//------------ declare public area for data downloaded from canvas--------

#ifndef _COURSE_INFO                                // struct for course including three structs: student
                                                    // information, assignment information, file(assignment itself) information
typedef struct{




    #ifndef _STU_INFO

    typedef struct{
        int Stu_Index;                              // index for retrieving information of student
        int Stu_Assigment_Grade_Current;            // grade students will get from this assignment
        int Stu_Assigment_Grade_Min;                // the minimum grade that students can get
        int Stu_Assigment_Grade_Max;                // the maximum grade that students can get
        double Stu_ID;                              // the ID number of student
        const char *Stu_Name;                             // student's name which has to be english
        const char *Stu_Mail_Addr;                        // student's email address


    } Stu_info;                                     // stu_info stores student information

    #define _STU_INFO
    #endif

    #ifndef _FILE_INFO

    typedef struct {
        const char *File_name_Origin[256];               // files's name
        const char *File_Ext_name;                  // file's extra name
                                                           // name if download group do not tell
        const char  *File_dir_Origin, *File_dir_N;         // position that file is located and the position where
                                                           // the copies of files and unzip files are?? we are going to store these new files under the same level where orignal files are sitting
        const char *File_Extname_N;                 // give something if u dont do anything

        int file_number;                            // how many files student submit
        int file_dir_err;                           // tell us whether certain file has vaild path
        int file_name_err;                          // tell us whether certain file has vaild name
        int file_name_valid;                        // whether file name is valid
        int file_zip_valid;                         // whether zipfile can be unzipped
                                                    // before unzipping file, we have to list files (by using
                                                    // listgetFileList(QString fileCompressed))
                                                    // and see whether these files follow name rule. If they dont,
                                                    // set file_name_valid to 0 and file_zip_valid 1


    } File_info;                                     // stores file (download from canvas, actually they are assignments) information. There are some seats reserved for class unzip, for now, we are not sure.

    #define _FILE_INFO
    #endif

    #ifndef _ASSIGNMENT_INFO

    typedef struct {

        const char *Assigment_Comment;                // grader's comment to a assignment
        const char *Assignment_Graph_Title;
        const char *Assignment_Title;           //
    } Assignment_info;                          // all the things about assignment
    #define _ASSIGNMENT_INFO
    #endif
    Stu_info S_info;
    File_info F_info;
    Assignment_info A_info;

} Course_info;                                   // Assigment_information is to store all information about assigment like

#define _COURSE_INFO
#endif

//---------------------------------------------------------------------------------

class Assignment_Unzip{
private:
    int m_Stu_Index, m_file_name_valid, m_file_zip_valid, m_F_number;
    const char *m_F_Exname, *m_F_Dir_Origin, *m_F_Dir_New;
    const char *m_F_name_Origin[256];
    const char *m_current_dir;
    double m_Stu_ID;
public:                                         // there are two methods;
/*    Assignment_Unzip(int Stu_Index, const char *F_Orname,
    const char *F_Exname, const char *F_Dir_Origin,
const char *F_Dir_New, const char *current_dir);  // reload your weapon ready to shoot*/

/* Using Stu_Index and Stu_ID to name the directory of each submited assignment;
 * file_name_valid indicates whether submitted file name follows rule, 1 is valid;
 * file_zip_valid indicates whether submitted zipfile can be unzipped, 1 is valid;
 * F_Dir_Origin is where download group put submitted assignment;
 * current_dir is where progame stay;
 * the function of this conductor is like reloading your weapon and prepare to shoot;
*/

    Assignment_Unzip(int Stu_Index, int file_name_valid,
                     int file_zip_valid, double Stu_ID,
                     const char *F_Dir_Origin, const char *current_dir,
                     const char *F_name_Origin[], int F_number);




    int A_Check_file(int &file_name_valid, int &m_file_zip_valid,
                     const char *F_Dir_New);       // check the file to see whether
                                                   // its name follows the rule and
                                                   // can or not be complied if file
                                                   // name is qualified
    void A_Send_mail(int f_c_flag, int f_q_flag, char const *s_mailaddress);      // notify student whose submitted assigment is not qualified
};

#endif // ASSIGMENT_UNZIP_H
