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

struct compare{
    bool operator()(int i, int j){
        return(i<j);
    }
}sort;

double Student::Assignment_Mean(){
    double sum_As=0;
    for(unsigned int i=0;i<Assignment_Marks.size();i++){
        sum_As+=Assignment_Marks[i];
    }
    return sum_As/Assignment_Marks.size();
}
double Student::Test_Mean(){
    double sum_Ts=0;
    for(unsigned int i=0;i<Test_Marks.size();i++){
        sum_Ts+=Test_Marks[i];
    }
    return sum_Ts/Test_Marks.size();
}
double Student::overall_Mean(){
    double sum_Ov=0;
    double sum_Ts=Student::Test_Mean();
    double sum_As=Student::Assignment_Mean();
    return sum_Ov=0.6*sum_Ts+0.15*sum_As;
}

void Student::Assignment_Arrange_LtoH(){

    std::sort(Assignment_Marks.begin(),Assignment_Marks.end(),sort);
}

void Student::Test_Arrange_LtoH(){
    std::sort(Test_Marks.begin(),Test_Marks.end(),sort);
}

double Student::Assignment_Median(){
    if(Assignment_Marks.size()%2==0){
        int upper=ceil((double)Assignment_Marks.size()/2);
        int lower=floor((double)Assignment_Marks.size()/2);
        return (Assignment_Marks[upper]+Assignment_Marks[lower])/2;
    }
    else{
        int position = (Assignment_Marks.size()+1)/2;
        return Assignment_Marks[position];
    }
}

double Student::Test_Median(){
    if(Test_Marks.size()%2==0){
        int upper=ceil((double)Test_Marks.size()/2);
        int lower=floor((double)Test_Marks.size()/2);
        return (Test_Marks[upper]+Test_Marks[lower])/2;
    }
    else{
        int position = (Test_Marks.size()+1)/2;
        return Test_Marks[position];
    }
}

void Student::setAssignment_Interval(){
    for(unsigned int i=0; i<Assignment_Marks.size();i++){
        if((Assignment_Marks[i]>=0)&&(Assignment_Marks[i]<5))
        {
            scoreInterval[0]++;
            std::cout<<Assignment_Marks[i];
        }
        else if((Assignment_Marks[i]>=5)&&(Assignment_Marks[i]<10))
        {
            scoreInterval[1]++;
        }
        else if((Assignment_Marks[i]>=10)&&(Assignment_Marks[i]<15))
        {
            scoreInterval[2]++;
        }
        else if((Assignment_Marks[i]>=15)&&(Assignment_Marks[i]<20))
        {
            scoreInterval[3]++;
        }
        else if((Assignment_Marks[i]>=20)&&(Assignment_Marks[i]<25))
        {
            scoreInterval[4]++;
        }
        else if((Assignment_Marks[i]>=25)&&(Assignment_Marks[i]<30))
        {
            scoreInterval[5]++;
        }
        else if((Assignment_Marks[i]>=30)&&(Assignment_Marks[i]<35))
        {
            scoreInterval[6]++;
        }
        else if((Assignment_Marks[i]>=35)&&(Assignment_Marks[i]<40))
        {
            scoreInterval[7]++;
        }
        else if((Assignment_Marks[i]>=40)&&(Assignment_Marks[i]<45))
        {
            scoreInterval[8]++;
        }
        else if((Assignment_Marks[i]>=45)&&(Assignment_Marks[i]<50))
        {
            scoreInterval[9]++;
        }
        else if((Assignment_Marks[i]>=50)&&(Assignment_Marks[i]<55))
        {
            scoreInterval[10]++;
        }
        else if((Assignment_Marks[i]>=55)&&(Assignment_Marks[i]<60))
        {
            scoreInterval[11]++;
        }
        else if((Assignment_Marks[i]>=60)&&(Assignment_Marks[i]<65))
        {
            scoreInterval[12]++;
        }
        else if((Assignment_Marks[i]>=65)&&(Assignment_Marks[i]<70))
        {
            scoreInterval[13]++;
        }
        else if((Assignment_Marks[i]>=70)&&(Assignment_Marks[i]<75))
        {
            scoreInterval[14]++;
        }
        else if((Assignment_Marks[i]>=75)&&(Assignment_Marks[i]<80))
        {
            scoreInterval[15]++;
        }
        else if((Assignment_Marks[i]>=80)&&(Assignment_Marks[i]<85))
        {
            scoreInterval[16]++;
        }
        else if((Assignment_Marks[i]>=85)&&(Assignment_Marks[i]<90))
        {
            scoreInterval[17]++;
        }
        else if((Assignment_Marks[i]>=90)&&(Assignment_Marks[i]<95))
        {
            scoreInterval[18]++;
        }
        else if((Assignment_Marks[i]>=95)&&(Assignment_Marks[i]<100))
        {
            scoreInterval[19]++;
        }
        else if(Assignment_Marks[i]>=100){
            scoreInterval[20]++;
        }
    }
}

int Student::getAssignment_Interval(int i){
    return scoreInterval[i];
}

/*void Student::print(){
    for(std::vector<double>::iterator it=Assignment_Marks.begin(); it!=Assignment_Marks.end();it++){
        std::cout<<' '<<*it;
    }
}
*/
