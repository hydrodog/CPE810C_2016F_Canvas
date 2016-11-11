#include "student.h"

int Student::Assignment_type=0;
int Student::numAssignments=0;
int Student::numTests=0;

void Student::Setstudent_id(int id){
    student_id=id;
}

int Student::Getstudent_id(){
    return student_id;
}

void Student::Set_Marks(int k,double marks){
    Marks[k]=marks;
}

double* Student::Get_Marks(){
    return Marks;
}

void Student::SetAssignmentType(int type) {
    Student::Assignment_type = type;
}

int Student::GetAssignment_type(void){
    return Assignment_type;
}

void Student::Set_numAssignments(){
    numAssignments++;
}

int Student::Get_numAssignments(){
    return numAssignments;
}

void Student::Set_numTests(){
    numTests++;
}

int Student::Get_numTests(){
    return numTests;
}


Student:: Student():student_id(0){
    for(int i=0; i< NUM_ASSIGNMENTS;i++)
        Marks[i]=0;
}

double Student::allAssignments_avg(){
    double sum=0;
    if (Student:: Assignment_type==1){
        for(int i=0;i<Student::numAssignments;i++){
            sum+=Marks[i];
        }
        sum/=Student::numAssignments;
    }
    return sum;
}

double Student::allTests_avg(){
    double a=0;
    if(Student::Assignment_type==2)
    {
        for(int i=0;i<numTests;i++){
            a+=Marks[i];
        }
        a/=NUM_ASSIGNMENTS;
    }
    return a;
}

double Student::Final_Grade(){
   return 0.25*Project_grade()+0.6*allTests_avg()+0.15*allAssignments_avg();
}

double Student::Project_grade(){
    return 0;
}
