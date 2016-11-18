#include<iostream>
#include<vector>
#include<string>
#include"PlagiarismDetector.hh"
using namespace std;

class detectPlagiarism {

private:
	//TO DO: Interface with either upload group/hw automation to pull the homework assignments and use them within This

	vector<string> testHomework; //The current homework assignment held in form tbd. String is placeholder for testing purposes

	vector<vector<string>> targetHomeworks; //The homework assignments to be tested against the current homework assignment

	vector<string> scores; //List of the comparison scores. String format is the current idea so the comparisons are easy to read

	int max(int a, int b){
		//helper function for lcs that determines the greater of two integers
		if(a > b)
			return a;
		else
			return b;
	}

	bool stringCompare(string a, string b){
		//Helper function for lcs that returns if two strings are equal
		if(a.compare(b) == a.size())
			return true;
		else
			return false;
	}

	int LCS(vector<string> a, vector<string> b, int i, int j){
		//This function computes the lcs of two vectors of strings
		int alen = a.size();
		int blen = b.size();
		if(i >= alen || j >= blen){
			return 0;
		}
		else if(stringCompare(a[i], b[j])) {
			return 1 + LCS(a, b, i + 1, j + 1);
		}
		else{
			return max(LCS(a, b, i + 1, j), LCS(a, b, i, j + 1));
		}

	}

public:

	vector<vector<string>> getHomeworks() {
		//This function will be used to pull the assignments to be compared.

	}

	vector<string> singleLcsTest(vector<vector<string>> targetH, int student){
		vector<string> results = vector<string>();
		vector<string> testH = targetH.at(student);
		for(int i = 0; i < targetH.size(); i++) {
			if(i != student)
				results.push_back("Submission " + to_string(student) + " is " + to_string((LCS(testH, targetH.at(i), 0, 0) * 100) / testH.size()) + "% similar to submission " + to_string(i + 1));
		}
		return results;
	}

	vector<vector<string>> classLcsTest(vector<vector<string>> targetH){
		vector<vector<string>> classResults = vector<vector<string>>();
		for(int i = 0; i < targetH.size(); i++){
			classResults.push_back(singleLcsTest(targetH, i));
		}
		return classResults;
	}
};
