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

public:

	vector<vector<string>> getHomeworks();

	vector<string> lcsTest(vector<string> testH, vector<vector<string>> targetH);



	//compile assignments
	//get tokens
	//run LCS
	//LCS / total tokens
	//return that
};


#endif // PLAGIARISM_DETECTOR_H
