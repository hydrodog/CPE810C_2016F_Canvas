#include<iostream>
#include<vector>
#include<string>
//#include"PlagiarismDetector.hh"
using namespace std;

class detectPlagiarism {

private:

	vector<string> testHomework; //The current homework assignment held in form tbd. String is placeholder for testing purposes

	vector<vector<string>> targetHomeworks; //The homework assignments to be tested against the current homework assignment

	vector<string> scores; //List of the comparison scores. String format is the current idea so the comparisons are easy to read

	int getLocW(string s)
	//This function determines where a token is in a string consisting of multiple tokens separated by non tokens
{
	int loc = 0;
	for(int i = 0; i < s.size(); i++)
	{
		if((i == s.size() - 1) && s[i] != ' ')
		{
			return -2;
		}

		else if(s[i] == '	' || s[i] == ' ' || (ispunct(s[i]) && s[i] != '_'))
		{
			return loc;
		}

		else 
		{
			loc++;
		}
	}
}



	int max(int a, int b){
		//helper function for lcs that determines the greater of two integers
		if(a > b)
			return a;
		else
			return b;
	}

	bool stringCompare(string a, string b){
		//Helper function for lcs that returns if two strings are equal
		if(a.compare(b) == 0)
			return true;
		else
			return false;
	}

public:

	vector<string> getTokens(string s)
	//this function takes in a string and tokenizes it, currently only views words or letters as tokens
	{
	vector<string> tokens = vector<string>();
	string tempString;
	int ind = 0;
	while(ind != -2)
	{
		if(s[0] == '	' || s[0] == ' ' || (ispunct(s[0]) && s[0] != '_')  )
		{
			s = s.substr(1, s.size() - 1);
		}
		
		if(!s.empty()){
			ind = getLocW(s);
		}
		else{
			ind = -2;
		}
		if(ind > 0)
		{
			tempString = s.substr(0, ind );
			tokens.push_back(tempString);
			s = s.substr(ind + 1, s.size() - (ind + 1));
		}
	}
	if(!s.empty())
	{
	
		int j = 0;
		while(j < s.size())
			{
				if(ispunct(s.at(j)) && s.at(j) != '_')
				{
					s.erase(s.begin() + j);
				}
				else
					j++;
			}
		if(!s.empty()) {
			tokens.push_back(s);
		}
	}

	return tokens;
}

	int LCS(vector<string> a, vector<string> b){
		//This function computes the lcs of two vectors of strings, added in dynamic implementation to  change order to O(mn) rather than O(2^n)
		const int alen = a.size();
		const int blen = b.size();

		vector<vector<int>> mem = vector<vector<int>>();

		for(int r = 0; r <= alen; r++){
			vector<int> temp = vector<int>();
			temp.assign(blen + 1, 0);
			mem.push_back(temp);
		}
		
		for(int k = alen; k >= 0; k--) {
			for(int l = blen; l >= 0; l--) {
				if(k >= alen || l >= blen){
					mem[k][l] = 0;
				} 
				else if(stringCompare(a[k], b[l])) {
					mem[k][l] = 1 + mem[k+1][l+1];
				}
				else{
					mem[k][l] = max(mem[k + 1][l], mem[k][l+1]);
				}
			
					
			}
		}
		return mem[0][0];
	}

//public: Functions below this will be public in the end. Functions above this will be private in the end but public now for testing purposes

	detectPlagiarism(){
		testHomework = vector<string>();
		targetHomeworks = vector<vector<string>> ();

	}

	vector<vector<string>> getHomeworks() {
		//This function will be used to pull the assignments to be compared.

	}

	


	vector<string> singleLcsTest(vector<vector<string>> targetH, int student){
		vector<string> results = vector<string>();
		vector<string> testH = targetH.at(student);
		for(int i = 0; i < targetH.size(); i++) {
			if(i != student)
				results.push_back("Submission " + to_string(student) + " is " + to_string((LCS(testH, targetH.at(i)) * 100) / testH.size()) + "% similar to submission " + to_string(i));  
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

