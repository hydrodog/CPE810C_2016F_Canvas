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

void Student::SetAssignment_Marks(double marks){
    Assignment_Marks.push_back(marks);
}

std::vector<double> Student::Get_Marks() const {
    return Assignment_Marks;
}

void Student::SetTest_Marks(double marks){
    Test_Marks.push_back(marks);
}

std::vector<double> Student::Get_TestMarks() const{
    return Test_Marks;
}

void Student::Set_AssignmentType(int type) {
    Student::Assignment_type = type;
}

int Student::GetAssignment_type(void){
    return Assignment_type;
}

void Student::Set_numAssignments(){
    numAssignments++;
}

int Student::Get_numAssignments()  {
    return numAssignments;
}

void Student::Set_numTests(){
    numTests++;
}

int Student::Get_numTests(){
    return numTests;
}


Student::Student():student_id(0){

}
