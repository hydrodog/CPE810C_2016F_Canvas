#include<iostream>
#include<vector>
#include<string>
#include"PlagiarismDetector.hh"
using namespace std;


	int detectPlagiarism::getLocW(string s){
	//This function determines where a token is in a string consisting of multiple tokens separated by non tokens

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
		return -2;
	}


	int detectPlagiarism::max(int a, int b){
		//helper function for lcs that determines the greater of two integers
		if(a > b)
			return a;
		else
			return b;
	}


	bool detectPlagiarism::stringCompare(string a, string b){
		//Helper function for lcs that returns if two strings are equal
		if(a.compare(b) == 0)
			return true;
		else
			return false;
	}


	vector<string> detectPlagiarism::getTokens(string s){
		//this function takes in a string and tokenizes it, currently only views words or letters as tokens
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


	int detectPlagiarism::LCS(vector<string> a, vector<string> b){
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


	detectPlagiarism::detectPlagiarism(){
		//generic constructor
		testHomework = vector<string>();
		targetHomeworks = vector<vector<string>> ();

	}


	vector<vector<string>> detectPlagiarism::getHomeworks() {
		//This function will be used to pull the assignments to be compared.
		return vector<vector<string>>();
	}


	vector<string> detectPlagiarism::singleLcsTest(vector<vector<string>> targetH, int student){
		//This function takes in a vector of assignments and compares a chosen assignment to the rest of the assignments
		vector<string> results = vector<string>();
		vector<string> testH = targetH.at(student);
		for(int i = 0; i < targetH.size(); i++) {
			if(i != student)
				results.push_back("Submission " + to_string(student) + " is " + to_string((LCS(testH, targetH.at(i)) * 100) / testH.size()) + "% similar to submission " + to_string(i));  
		}
		return results;
	}


	vector<vector<string>> detectPlagiarism::classLcsTest(vector<vector<string>> targetH){ 
		//Runs a comparison of each assignment with all the others
		vector<vector<string>> classResults = vector<vector<string>>();
		for(int i = 0; i < targetH.size(); i++){
			classResults.push_back(singleLcsTest(targetH, i));
		}
		return classResults;
	}
