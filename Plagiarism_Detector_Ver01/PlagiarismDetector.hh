#ifndef PLAGIARISM_DETECTOR_H
#define PLAGIARISM_DETECTOR_H

#include<iostream>
#include<vector>
#include<string.h>
using namespace std;

class detectPlagiarism {
private:

	vector<string> testHomework; //The current homework assignment held in form tbd. String is placeholder for testing purposes

	vector<vector<string>> targetHomeworks; //The homework assignments to be tested against the current homework assignment

	vector<string> scores; //List of the comparison scores. String format is the current idea so the comparisons are easy to read

	int getLocW(string s); //This function determines where a token is in a string consisting of multiple tokens separated by non tokens

	int max(int a, int b); //helper function for lcs that determines the greater of two integers

	bool stringCompare(string a, string b); //Helper function for lcs that returns if two strings are equal



public:

	vector<string> getTokens(string s); //this function takes in a string and tokenizes it, currently only views words or alphanumerics as tokens

	int LCS(vector<string> a, vector<string> b); //This function computes the lcs of two vectors of strings, added in dynamic implementation to  change order to O(mn) rather than O(2^n)

	//This line divides the true public functions with those that are public for testing. The above two are critical to work so they are public now for testing
	//In the final implementation they will solely be called by the below functions

	detectPlagiarism(); //generic constructor

	vector<string> singleLcsTest(vector<vector<string>> targetH, int student); //This function takes in a vector of assignments and compares a chosen assignment to the rest of the assignments in the vector

	vector<vector<string>> classLcsTest(vector<vector<string>> targetH); //Runs a comparison of each assignment with all the others

	vector<vector<string>> getHomeworks(); //Takes in the homeworks and formats them to be compared.

	vector<vector<string>> getVecs(string fpath1, string fpath2); //Takes in two file paths and returns a vector containing both tokenized

	string quickFileComp(string fpath1, string fpath2);//Takes in two assignment file paths and returns the comparison comment

};

#endif // PLAGIARISM_DETECTOR_H