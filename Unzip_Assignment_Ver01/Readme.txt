/**************** Fangming Zhao 11/21/2016 ****************
 * object: Assignment_Unzip.cpp; Assignment_Unzip; main.cc
 * action: rewrite whole method Check_file() in Assignment_Unzip.
 *         cpp; this time, I use two array variables to store
 *         naming rule. Also creating a new data struct called
 *         homework. Im planning to use class instead of data
 *         struct in the next version. Maybe class is safer.
 *
 * program ver: v0.94
 /******************** He Song 11/17/2016 ******************
 * object: smtp.cpp
 * action: edit the smtp.cpp to make it can use the stevens
 *         email account to send email.
 * program ver: v0.77
/******************** He Song 11/16/2016 ******************
 * object: smtp.cpp;smtp.h
 * action: add this two file to make a new class in the
 *         assignment part. This will make the others use
 *	   send email easily than before.
 * program ver: v0.76
/**************** Fangming Zhao 11/12/2016 ****************
 * object: Assignment_Unzip.cpp; Assignment_Unzip
 * action: add new lines after getFileList() for determining
 *         whether zipfile has files inside or can be
 *         unzipped (start at line 91) . add new variable
 *         File_in_Index (line 45), file_unzip_dir and
 *         file_name_inzip[20] in data structure in Assignment
 *         _Unzip.
 * program ver: v0.75
/**************** Fangming Zhao 11/11/2016 ****************
 * object: Assignment_Unzip.cpp; Assignment_Unzip.hh
 * action: [object: Assignment_Unzip.cpp]: add new lines
 *         for indicating whether zipfile can be unzip
 *         (start at line 112); Using m_file_zip_valid and
 *         m_file_name_valid as reference to indicate whether
 *         file can be unzip and name is valid and then pass
 *         the value to f_q_flag and f_c_flag(start at line
 *         52);
 *         [Assignment_Unzip.hh]: change the name of data
 *         structure, and add and modify some commits (start
 *          at line 30);
 * program ver: v0.74
/******************** He Song 11/11/2016 ******************
 * object: Assignment_Unzip.cpp
 * action: add a send_mail function to class in windows OS
 * program ver: v0.73
/******************** He Song 11/11/2016 ******************
 * object: main.cpp
 * action: add a new way to get current dir in windows OS
 * program ver: v0.72
/**********************************************************
 * author : Fangming Zhao
 * working OS: MacOs Sierra
 * IDE: Qt Creator 4.1.0
 * tool: C++
 * group: C/zip file rules
 * group member: Zheao Ma, He Song, Yuan Zhou
 * collaborator: Zheao Ma, He Song, Yuan Zhou
 * program name: Unzip_Assignment_Ver01
 * program ver: v0.7
 *
 ***********************************************************/
