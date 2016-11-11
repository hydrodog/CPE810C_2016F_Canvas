#ifndef CATEGORY_H
#define CATEGORY_H


class Category
{
private:
    double homework[40][10]={0}; //store scores of all 10 homeworks for all 40 students
    double test[40][3]={0};//store scores of all 3 tests for all 40 students
    double project[40]={0};//store scores of project of all 40 students

public:
    Category();
    void setHomework(double homeworkgrade);//testgrade is a function from data group
    void setTest(double testgrade);//testgrade is a function from data group
    void setProject(double projectgrade);//projectgrade is a function from data group
    double getHomework();
    double getTest();
    double getProject();

    //I think we can put all this statistic calculation into another class file
    void arrangmentH_L();//arrage all scores from the highest to lowest or vice versa.
    void arrangmentH_L();
    double mean();
    double median();
    double variance();
};

#endif // CATEGORY_H
