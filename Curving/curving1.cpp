#include "curving.h"
#include <math.h>
#include <iostream>
using namespace std;

Curving::Curving(double *data, int size){
    m_confirm = false;
    m_originalGrades = data;
    m_size = size;
    m_curvedGrades = new double[m_size];
    for(int i = 0; i < size; i++)
        m_curvedGrades[i] = m_originalGrades[i];
    }

// perform a linear curve on grades
void Curving::linCurve(int curve){
    for(int i = 0; i < m_size; i++)
        m_curvedGrades[i] = m_originalGrades[i] + curve;
}

// perform 10*sqrt(g) curve on grades
void Curving::rootCurve(){
    for(int i = 0; i < m_size; i++)
        m_curvedGrades[i] = 10*sqrt(m_originalGrades[i]);
}

// returns curved array of grades
double* Curving::returnCurve() const {
    return m_curvedGrades;
}

// accept or deny changes to grades
double Curving::statisticsoflin() {
    double mean=0;
    double variance=0;
   for(int i = 0; i < m_size; i++){
       mean=mean+ m_curvedGrades[i];
   }
     mean=mean/m_size;
     for(int i = 0; i < m_size; i++){
         variance=variance + (pow( m_curvedGrades[i]-mean,2));
          }
     cout <<mean<<endl;
     cout <<variance <<endl;
     return variance;
    }

double Curving::statisticsofroot() {
    double mean=0;
    double variance=0;
   for(int i = 0; i < m_size; i++){
       mean=mean+ m_curvedGrades[i];
   }
     mean=mean/m_size;
     for(int i = 0; i < m_size; i++){
         variance=variance + (pow( m_curvedGrades[i]-mean,2));
          }
     cout <<mean<<endl;
     cout <<variance <<endl;
     return variance;
    }

void acceptChanges(){

}


