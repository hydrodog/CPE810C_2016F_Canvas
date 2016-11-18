#include "category.h"

double category::Assignment_Mean(){
    double sum_As=0;
    for(unsigned int i=0;i<Assignment_Marks.size();i++){
        sum_As+=Assignment_Marks[i];
    }
    return sum_As/Assignment_Marks.size();
}
double category::Test_Mean(){
    double sum_Ts=0;
    for(unsigned int i=0;i<Test_Marks.size();i++){
        sum_Ts+=Test_Marks[i];
    }
    return sum_Ts/Test_Marks.size();
}
double category::overall_Mean(){
    double sum_Ov=0;
    double sum_Ts=category::Test_Mean();
    double sum_As=category::Assignment_Mean();
    return sum_Ov=0.6*sum_Ts+0.15*sum_As;
}

void category::Assignment_Arrange_HtoL(){
    std::sort(sorted_Assignment.begin(),sorted_Assignment.end());
}

void category::Test_Arrange_HtoL(){
    std::sort(sorted_Test.begin(),sorted_Test.end());
}

double category::Assignment_Median(){
    if(sorted_Assignment.size()%2==0){
        int upper=ceil((double)sorted_Assignment.size()/2);
        int lower=floor((double)sorted_Assignment.size()/2);
        return (sorted_Assignment[upper]+sorted_Assignment[lower])/2;
    }
    else{
        int position = (sorted_Assignment.size()+1)/2;
        return sorted_Assignment[position];
    }
}

double category::Test_Median(){
    if(sorted_Test.size()%2==0){
        int upper=ceil((double)sorted_Test.size()/2);
        int lower=floor((double)sorted_Test.size()/2);
        return (sorted_Test[upper]+sorted_Test[lower])/2;
    }
    else{
        int position = (sorted_Test.size()+1)/2;
        return sorted_Test[position];
    }
}

double category::Assignment_Variance(){
    double sum=0;
    double mean=category::Assignment_Mean();
    for(unsigned int i=0;i<Assignment_Marks.size();i++){
        sum+=pow(Assignment_Marks[i]-mean,2);
    }
    return sum/Assignment_Marks.size();
}

double category::Test_Variance(){
    double sum=0;
    double mean=category::Test_Mean();
    for(unsigned int i=0;i<Test_Marks.size();i++){
        sum+=pow(Test_Marks[i]-mean,2);
    }
    return sum/Test_Marks.size();
}
