#include <math.h>
#include "Curving.h"

Curving::Curving(){
	m_curvedGrades[] = { 0 };
}

// perform a linear curve on grades
void Curving::linCurve(int curve, int length){
	for(int i = 0; i < length; i++)
		m_curvedGrades[i] = m_originalGrades[i] + curve;
	
}

// perform 10*sqrt(g) curve on grades
void Curving::rootCurve(int length){
    for(int i= 0; i < length; i++)
	    m_curvedGrades[i] = 10*sqrt(m_originalGrades[i]);
	
}

// returns curved array of grades
double Curving::returnCurve(){
	return m_curvedGrades;
}

// accept or deny changes to grades
void Curving::acceptChanges(){
	
}
