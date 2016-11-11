#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H


class assignment
{
private:
    double grade[40]={0}; //storing all the grade for each student in this specific assignment
public:
    assignment();
    void setGrade(double homeworkgrade); //homeworkgrade is a function of class data
    double getGrade();

    //I think we can put all this statistic calculation into another class file
    void arrangmentH_L();//arrage all scores from the highest to lowest or vice versa.
    void arrangmentH_L();
    double mean();
    double median();
    double variance();
};
#endif // ASSIGNMENT_H
