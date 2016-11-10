#include <QCoreApplication>

#include <iostream>
#include <string>
#include <Assignment_Unzip.hh>
#include <mach-o/dyld.h>
#include <cstring>                       // for using strrchr()
#include <cstdlib>

#ifdef WIN32
#include "windows.h"                    // by using GetModuleFileName()
#endif

using namespace std;




int main(){

    int HOWMANY_STU = 10;               // for simulating

    Course_info *stu=new Course_info[HOWMANY_STU];      // HOWMANY_STU is dyn

    for(int i=HOWMANY_STU-1; i>=0; i--){

        stu[i].A_info.Assigment_Comment = "good!";
        stu[i].F_info.file_number = 3;
        for(int j = stu[i].F_info.file_number-1; j>=0; j--)     // student may submit mutiple assignments
        {
            stu[i].F_info.File_name_Origin[j] = "HW6.txt";
        }
        stu[i].F_info.File_Ext_name = ".cpp";

        stu[i].F_info.File_dir_Origin = "/Users/fangmingzhao/course/Project/build-Unzip_Assignment_Ver01-Desktop_Qt_5_7_0_clang_64bit-Debug/59380_0";         // given by download

        stu[i].F_info.file_name_valid = 0;       // initialize file name ok flag;
        stu[i].F_info.file_zip_valid = 0;         // initialize zip ok flag
/*      strcat() combine two string together
        we set different directories for every student (this work can be
        done by download group)



*/
//        stu[i].F_info = {"noway",".txt", "\\new1\\hello", "\\old1\\byebye", 1,1,0,0};

        stu[i].S_info.Stu_Assigment_Grade_Current = 90;
        stu[i].S_info.Stu_Assigment_Grade_Max = 100;
        stu[i].S_info.Stu_Assigment_Grade_Min = 0;
        stu[i].S_info.Stu_ID = 10419999;
        stu[i].S_info.Stu_Index = i;
        stu[i].S_info.Stu_Mail_Addr = "cplusplus@qt.com";
        stu[i].S_info.Stu_Name = "Michael";


    }

    delete[] stu;

    cout.precision(10);
    cout << stu[13].S_info.Stu_Index << '\n';
//--------------------------------------------------------------------
// get current directory and store it in current_pro_dir
    uint32_t dir_buf_size = sizeof(current_pro_dir);

    if (_NSGetExecutablePath(current_pro_dir, &dir_buf_size) == 0)
    {
        cout << dir_buf_size << '\n';
        char *p = strrchr(current_pro_dir, '/');
#ifdef WIN32
        char *p = GetModuleFileNameW();
#endif
        *p = 0;
//                cout << *p;
        printf("executable path is %s\n", current_pro_dir);
        Get_dir_OK = 1;
    }
    else{
        printf("buffer too small; need size %u\n", dir_buf_size);
        Get_dir_OK = 0;
    }
#ifdef WIN32
    if(!GetModuleFileName(Null, current_pro_dir, 256)){
        printf("executable path is %s\n", current_pro_dir);
        Get_dir_OK = 1;
    }
    else{
        printf("fail to get path information!\n");
        Get_dir_OK = 0;
    }
#endif
// get current directory and store it in current_pro_dir
//--------------------------------------------------------------------
/***********************************************************************
 * this is reserved section for building sub-directory for each student
 * , if download group do not do that and have a way to solve rename problem
 *
 ***********************************************************************/


   // for(int i=HOWMANY_STU-1; i>=0; i--){
    int i = 1;
        Assignment_Unzip a(stu[i].S_info.Stu_Index, stu[i].F_info.file_name_valid,
                           stu[i].F_info.file_zip_valid, stu[i].S_info.Stu_ID,
                           stu[i].F_info.File_dir_Origin, current_pro_dir,
                           stu[i].F_info.File_name_Origin, stu[i].F_info.file_number);  // reload your weapon ready to shoot

        //a.A_Check_file(stu[i].F_info.file_name_valid, stu[i].F_info.file_zip_valid, stu[i].F_info.File_dir_N);       // figure out whether file student submit follow name rule or can be complied

        if(stu[i].F_info.file_zip_valid && stu[i].F_info.file_name_valid){                  // if file's name does not follow rule or can't be complied, send mail;
          //  a.A_Send_mail(stu[i].F_info.file_zip_valid, stu[i].F_info.file_name_valid, stu[i].S_info.Stu_Mail_Addr);
      //  }
    }

}
