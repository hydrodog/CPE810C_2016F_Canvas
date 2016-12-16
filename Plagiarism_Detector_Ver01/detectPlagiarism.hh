#ifndef DETECT_PLAGIARISM_H
#define DETECT_PLAGIARISM_H

#include<iostream>
#include<vector>
#include<string.h>
using namespace std;

class detectPlagiarism {
private:

	vector<string> testHomework; //The current homework assignment held in form tbd. String is placeholder for testing purposes.

	vector<vector<string>> targetHomeworks; //The homework assignments to be tested against the current homework assignment.

	vector<string> scores; //List of the comparison scores. String format is the current idea so the comparisons are easy to read.

	int getLocW(string s); //This function determines where a token is in a string consisting of multiple tokens separated by non tokens.

	int max(int a, int b); //helper function for lcs that determines the greater of two integers.

	bool stringCompare(string a, string b); //Helper function for lcs that returns if two strings are equal.

	int LCS(vector<string> a, vector<string> b); //This function computes the lcs of two vectors of strings, added in dynamic implementation to  change order to O(mn) rather than O(2^n)

	vector<vector<string>> getVecs(string fpath1, string fpath2); //Takes in two file paths and returns a vector containing both tokenized.

	vector<string> getVec(string fpath1); //Takes in a file path and converts the file into a vector of the it tokenized as strings.

	vector<vector<string>> getDynVecs(vector<string> paths); //Takes in a vector of paths and returns a vector of them as tokenized vectors of strings.

public:

	detectPlagiarism(); //generic constructor

	vector<string> getTokens(string s); //this function takes in a string and tokenizes it, currently only views words or alphanumerics as tokens
	
	string quickComp(vector<string> a1, vector<string> a2); //Returns a sentence saying the comparsion of two assignments (String).

	string quickComp(string fpath1, string fpath2); //Takes in two assignment file paths and returns a sentence saying the comparison of the two assignments (string).

	vector<string> singleLcsTest(vector<vector<string>> targetH, int student); //This function takes in a vector of assignments and compares a chosen assignment to the rest of the assignments in the vector.

	vector<string> singleLcsTest(); //This function allows the user to input as many file paths as needed and runs singleLcsTest with the first file as the target.
	
	vector<string> singleLcsTest(vector<string> paths); //This function allows the user to add as many file paths as needed through a vector of strings and then calls singleLcsTest.

	vector<vector<string>> classLcsTest(vector<vector<string>> targetH); //Runs a comparison of each assignment with all the others.

	vector<vector<string>> classLcsTest(); //This function allows the user to input as many file paths as needed and runs classLcsTest on the files.

	vector<vector<string>> classLcsTest(vector<string> paths); //This function allow sthe user to add as many file paths as needed through a vector of strings and then calls classLcsTest.
};

#endif // DETECT_PLAGIARISM_H