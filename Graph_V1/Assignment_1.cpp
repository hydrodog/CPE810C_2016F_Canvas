#include <iostream>
#include <string>		// For utilizing strings
using namespace std;

int size=10;
struct Assignment{
    string name;		// Name of student
    int idnum;			// Student ID number
    int* assignments;			// Pointer to an array of test scores
};

// Function Prototype(s)
int inputStudents();				// Asks user for number of students
int inputassignments();					// Asks user for number of Assignments scores
string inputName();					// Asks uer for each student's name
int inputID();						// Asks user for each student's ID number
int *inputScores(int);				// Asks user for the Assignments scores for each student
void display();		// Displays each student's name,ID#,number of Assignments, scores


int main(){

    // Create a dynamic array of the Assignment. Array size is based upon user input given in
    // the inputStudents function.
    Assignment* studentList;
    int size = inputStudents();
    studentList = new Assignment[size];

    // Check for possible memory allocation errors. if number of students =0 then error is found, end program.
    if (studentList == NULL){
        cout << "Memory Allocation Error!";
        system("pause");
        return 0;
    }


    for (int count = 0; count <= size; count++){
        studentList[count].name = inputName();
        studentList[count].idnum = inputID();
        studentList[count].assignments = inputScores(1);
        cout << studentList[count].name << " " << studentList[count].idnum << " "
        << studentList[count].assignments<<endl;
    }

    //display();TODO:Write a display function

    delete [] *studentList;

    system ("pause");
    return 0;
}

int inputStudents(){

    int students;
    cout << "Number of students in your class" << endl;
    cin >> students;

    return students;
}
int inputassignments(){

    int assignments;
    cout << "How many Assignments will there be?" << endl;
    cin >> assignments;

    return assignments;
}

string inputName(){

    string name;
    cout << "Enter the student's name: ";
    cin >> name;

    return name;

}

int inputID(){

    int idNum;
    cout << "Enter the student's CWID Number ";
    cin >> idNum;

    return idNum;

}

int *inputScores(int numOfassignments){

    int *scores;
    scores = new int[numOfassignments];

    cout << "Enter Assignment scores and press ENTER after each score." << endl;

    for (int count = 0; count <= numOfassignments; count++){
        cout << "Score " << (count + 1) << ": ";
        cin >> scores[count];
    }

    return scores;
}

/*void display(){

    for (int count = 0; count < size; count++)
        cout << studentList[count].name << " " << studentList[count].idnum << " "
        << studentList[count].score<<endl;

    return;
}*/

