#include <iostream>
#include <vector>
#include <string>
#include "PlagiarismDetector.hh"

using namespace std;

int main (){

  detectPlagiarism c;
  string s = "Hello";
  string a = "Hello";
  vector<string> i;
  vector<string> b;
  i = c.getTokens(s);
  b = c.getTokens(a);
  cout << c.LCS(i,b) << endl;


  return 0;

}
