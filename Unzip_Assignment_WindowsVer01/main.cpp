#include <QCoreApplication>

#include "zipfile.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <cstring>                       // for using strrchr()
#include <cstdlib>
#include <vector>
#include <sstream>
// for converting double to string
#include <winsock2.h>

/**********************************************************
 * author : Fangming Zhao, Zheao Ma
 * working OS: Windows 7
 * IDE: Qt Creator 4.1.0
 * tool: C++
 * group: C/zip file rules
 * group member: Zheao Ma, He Song, Yuan Zhou
 * program name: Unzip_Assignment_Ver01
 * program ver: v 1.00
 *
 ***********************************************************/

using namespace std;

int main(){
    std::ostringstream temp1;
    const char* temp3;

/*------------------- the following content is made for testing whole program ---------------------
 * Gboing to rewrite this section. instead of using "new", vector is better way to manage memory! Maybe take a
 * whole week to do that! haha~~
 *
* no matter what's HomeWork, students number and who are they are certain. Therefore the data structure
* HomeWork has the same level with data structure Student. They are independent with each other.
*
*/

    int HOWMANY_HW = 2;                 // got from outside;

    const char *rule_Main_test[2];
    const char *rule_Extra_test[2];
    rule_Main_test[0] = "main";
    rule_Main_test[1] = "*";
    rule_Extra_test[0] = ".cc";
    rule_Extra_test[1] = ".cpp";
/***************************************
 * use vector to inite the data struct
 *    vector<HomeWork> b;
 *   for(int i=0;i<10;i++){
 *       HomeWork.rule_num = 2;
 *       b.push_back(i);
 *   }
 *********************************************/

        HomeWork *HW = new HomeWork[HOWMANY_HW];        // it is really hard to monitor array
        if(HW == NULL){
            cout << "fail to allocate memory!";
            exit(0);
        }

        for (int i=0; i < HOWMANY_HW; i++){
            HW[i].rule_num = 2;
//          HW[i].File_name_rule_Main = new const char*[2];       // keep them for referring
//          HW[i].File_name_rule_Extra = new const char*[2];

            for(int j = 0; j < HW[i].rule_num; j++){
                HW[i].File_name_rule_Main[j] = rule_Main_test[j];
                HW[i].File_name_rule_Extra[j]= rule_Extra_test[j];
  //            cout << HW[i].File_name_rule_Main[j] << '\n';
            }
//          delete[] HW[i].File_name_rule_Extra;
//          delete[] HW[i].File_name_rule_Main;
        }


    delete[] HW;

    int HOWMANY_STU = 10;               // for simulating;
//--------------------- stimulate pass data to Student struct --------------------------
    Student *stu=new Student[HOWMANY_STU];      // HOWMANY_STU is dyn
    if(stu == NULL){
        cout << "fail to allocate memory!";
        exit(0);
    }
    for(int i=HOWMANY_STU-1; i>=0; i--){

        stu[i].A_info.Assigment_Comment = "good!";
        stu[i].F_info.file_number = 3;
        for(int j = stu[i].F_info.file_number-1; j>=0; j--)     // student may submit mutiple assignments
        {
            stu[i].F_info.File_name_Origin[j] = "SLAM.zip";
        }
//        for(string ref:stu[i].F_info.File_dir_N_new)
//            ref = "haha";

//        cout << stu[i].F_info.File_dir_N_new[0];
        stu[i].F_info.File_dir_N = "D:/SLAM";
        stu[i].F_info.File_name_Extra = ".cpp";

        stu[i].F_info.File_dir_Origin = "D:/";         // given by download

        stu[i].F_info.file_name_valid = -1;       // initialize file name ok flag;
        stu[i].F_info.file_zip_valid = -1;         // initialize zip ok flag
/*      strcat() combine two string together
        we set different directories for every student (this work can be
        done by download group)
*/
//        stu[i].F_info = {"noway",".txt", "\\new1\\hello", "\\old1\\byebye", 1,1,0,0};

        stu[i].S_info.Stu_Assigment_Grade_Current = 90;
        stu[i].S_info.Stu_Assigment_Grade_Max = 100;
        stu[i].S_info.Stu_Assigment_Grade_Min = 0;
        stu[i].S_info.Stu_ID = 10405887;
        stu[i].S_info.Stu_Index = i;
//        stu[i].S_info.Stu_Mail_Addr = "cplusplus@qt.com";
        stu[i].S_info.Stu_Name = "Jerry";
/*
 *      temp1 << stu[i].S_info.Stu_ID;
        std::string temp2 = temp1.str();
        if(stu[i].F_info.File_dir_N == NULL || &temp2 == NULL) return NULL;
        while(*stu[i].F_info.File_dir_N++);
        stu[i].F_info.File_dir_N--;
//        while(*stu[i].F_info.File_dir_N++ = temp2);
*/

    }

    delete[] stu;
 //   char *buf;
 //   getcwd(buf, sizeof(buf));
 //   cout << buf << '\n';
    cout.precision(10);
    cout << stu[13].S_info.Stu_Index << '\n';
/*-------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------*/

//--------------------------------------------------------------------
/***********************************************************************
 * this is reserved section for building sub-directory for each student under
 * working directory
 *
 *
 ***********************************************************************/


 /*---------------- for(int i=HOWMANY_STU-1; i>=0; i--){ ---- reserved for testing ---------------------------*/

    int i = 1;
        Assignment_Unzip a(stu[i].S_info.Stu_Index, stu[i].F_info.file_name_valid,
                           stu[i].F_info.file_zip_valid, stu[i].S_info.Stu_ID,
                           stu[i].F_info.File_dir_Origin, current_pro_dir,
                           stu[i].F_info.File_name_Origin, stu[i].F_info.file_number,HW[i].rule_num
                           ,HW[i].File_name_rule_Main, HW[i].File_name_rule_Extra);  // reload your weapon ready to shoot
        a.test();
        a.A_Check_file(stu[i].F_info.file_name_valid, stu[i].F_info.file_zip_valid,
                       stu[i].F_info.file_name_qualified);       // figure out whether file student submit
                                                        // follow name rule or can be unzipped

//        if(stu[i].F_info.file_zip_valid && stu[i].F_info.file_name_valid){    // if file's name does not follow
//                                                                              // rule or can't be Unzipped, send
//                                                                              // them mail;
//            a.A_Send_mail(stu[i].F_info.file_zip_valid, stu[i].F_info.file_name_valid);

//        }

        a.A_Send_mail();
}
