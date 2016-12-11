#include "curving.h"

Curving::Curving(vector<double> data){
    m_confirm = false;
    m_originalGrades = data;
    m_curvedGrades = data;
    m_size = data.size();
}

// perform a linear curve on grades
void Curving::linCurve(double curve){
    for(int i = 0; i < m_size; i++)
        m_curvedGrades[i] = m_originalGrades[i] + curve;
    m_typeCurve = false;
}

// perform 10*sqrt(g) curve on grades
void Curving::rootCurve(){
    for(int i = 0; i < m_size; i++)
        m_curvedGrades[i] = 10*sqrt(m_originalGrades[i]);
    m_typeCurve = true;
}

// returns curved array of grades
vector<double> Curving::returnCurve() const {
    return m_curvedGrades;
}

// accept or deny changes to grades
void Curving::acceptChanges(){
    string s;
    if (m_typeCurve) // root curve
        s = "root curve";
    else
        s = "linear curve";
    char c;

    while(1){
        cout << "You performed a " << s << " on the grades\n"
                "Do you want to keep these changes? (Y or N)\n";
        cin >> c;
        if(c == 'N' || c == 'n'){
            m_curvedGrades = m_originalGrades;
            cout << "Your changes have not been saved\n";
            break;
        }
        else if(c == 'Y' || c == 'y') {
            m_originalGrades = m_curvedGrades;
            cout << "Your changes have been saved\n";
            break;
        }
        else
            cout << "Please enter Y for yes or N for no\n";
    }

}
