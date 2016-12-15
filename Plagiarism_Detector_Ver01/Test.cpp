#include <iostream>
#include <vector>
#include <string>
#include "detectPlagiarism.hh"

using namespace std;

int main (){

  detectPlagiarism test = detectPlagiarism();
  string sa = "Hello this is the first sentence";
  string sb = "Hello this is the second sentence";
  vector<string> student1 = test.getTokens(sa);
  vector<string> student2 = test.getTokens(sb);
  vector<vector<string>> students = vector<vector<string>>();
  students.push_back(student1);
  students.push_back(student2);
  cout << test.singleLcsTest(students, 1).at(0) << endl;

  vector<vector<string>> files = vector<vector<string>>();

  cout << test.quickFileComp("test3.txt", "test4.cpp") << endl;

  vector<string> inpTest = test.fileSingleLcsTest();

  cout << inpTest.at(0) << endl;

  system("pause");
  return 0;

}