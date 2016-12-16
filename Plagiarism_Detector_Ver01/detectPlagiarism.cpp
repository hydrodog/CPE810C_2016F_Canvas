#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include"detectPlagiarism.hh"
using namespace std; 


	int detectPlagiarism::getLocW(string s){
	//This function determines where a token is in a string consisting of multiple tokens separated by non tokens

		int loc = 0;
                for(unsigned int i = 0; i < s.size(); i++)
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


	vector<string> detectPlagiarism::singleLcsTest(vector<vector<string>> targetH, int student){
		//This function takes in a vector of assignments and compares a chosen assignment to the rest of the assignments
		vector<string> results = vector<string>();
		vector<string> testH = targetH.at(student);
		for(int i = 0; i < targetH.size(); i++) {
			if(i != student)
				results.push_back("Submission " + to_string(student + 1) + " is " + to_string((LCS(testH, targetH.at(i)) * 100) / testH.size()) + "% similar to submission " + to_string(i + 1) + ". ");  
		}
		return results;
	}


	vector<vector<string>> detectPlagiarism::classLcsTest(vector<vector<string>> targetH){ 
		//Runs a comparison of each assignment with all the others
		vector<vector<string>> classResults = vector<vector<string>>();
                for(unsigned int i = 0; i < targetH.size(); i++){
			classResults.push_back(singleLcsTest(targetH, i));
		}
		return classResults;
	}

	string detectPlagiarism::quickComp(vector<string> a1, vector<string> a2){
		//Returns a sentence saying the comparsion of two assignments (String).
		int lt = LCS(a1, a2) * 100;
		return "Submission 1 is " + to_string(lt / a1.size()) + "% similar to submission 2. Submission 2 is " + to_string(lt / a2.size()) + "% similar to submission 1.";
	}

	vector<string> detectPlagiarism::getVec(string fpath1){
		//Takes in a file path and converts the file into a vector of the it tokenized as strings.
		string hw;
		string line;
		vector<string> result = vector<string>();
		ifstream file;
		file.open(fpath1);
		while(getline(file, line)){
			hw += line;
			hw += " ";
		}
		file.close();
		return getTokens(hw);
	}


	vector<vector<string>> detectPlagiarism::getVecs(string fpath1, string fpath2){
		//Takes in two file paths and converts them into vectors of string to compare using LCS
		string hw1;
		string hw2;
		string line;
		vector<vector<string>> result = vector<vector<string>>();
		ifstream file;
		file.open(fpath1);
		while(getline(file, line)){
			hw1 += line;
			hw1 += " ";
		}
		file.close();
		file.open(fpath2);
		while(getline(file, line)){
			hw2 += line;
			hw2 += " ";
		}
		file.close();
		result.push_back(getTokens(hw1));
		result.push_back(getTokens(hw2));
		return result;
	}


	string detectPlagiarism::quickComp(string fpath1, string fpath2){
		//Takes in two assignment file paths and returns a sentence saying the comparison of the two assignments (string).
		return quickComp(getVec(fpath1), getVec(fpath2));
	}

	vector<vector<string>> detectPlagiarism::getDynVecs(vector<string> paths){
		//Takes in a vector of paths and returns a vector of them as tokenized vector of strings.
		int s = paths.size();
		vector<vector<string>> assignments;
		for(int i = 0; i < s; i++) {
			assignments.push_back(getVec(paths.at(i)));
		}
		return assignments;
	}

	vector<string> detectPlagiarism::singleLcsTest(){
		//This function allows the user to input as many file paths as needed and runs singleLcsTest with the first file as the target.
		vector<string> result;
		vector<vector<string>> vecs;
		vector<string> paths;

		string fname = "initial";

		while(fname != "END") {
			cout << "Enter file paths one at a time, enter END to complete the entries. First file entered will be compared against all others" << '\n' << "File Path: ";
			cin >> fname;
			cout << '\n';
			if(fname != "END")
				paths.push_back(fname);
		}

		vecs = getDynVecs(paths);

		result = singleLcsTest(vecs, 0);

		return result;
	}


	vector<vector<string>> detectPlagiarism::classLcsTest(){
		//This function allows the user to input as many file paths as needed and runs classLcsTest on the files.
		vector<vector<string>> results;
		vector<vector<string>> vecs;
		vector<string> paths;

		string fname = "initial";

		while(fname != "END") {
			cout << "Enter file paths one at a time, enter END to complete the entries" << '\n' << "File Path: ";
			cin >> fname;
			cout << '\n';
			if(fname != "END")
				paths.push_back(fname);
		}

		vecs = getDynVecs(paths);

		results = classLcsTest(vecs);

		return results;
	}


	vector<vector<string>> detectPlagiarism::classLcsTest(vector<string> paths){

		vector<vector<string>> results;
		vector<vector<string>> vecs;

		vecs = getDynVecs(paths);

		results = classLcsTest(vecs);

		return results;

	}

	
	vector<string> detectPlagiarism::singleLcsTest(vector<string> paths){

		vector<string> results;
		vector<vector<string>> vecs;

		vecs = getDynVecs(paths);

		results = singleLcsTest(vecs, 0);

		return results;

	}
