#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <map>
#include <bitset>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<set>
#include "bit.h"

using namespace std;


string toBinary(int n)
{
	std::string r;
	while (n != 0) { r = (n % 2 == 0 ? "0" : "1") + r; n /= 2; }
	return r;
}

bool do_u_have_Mins()
{

	string answer;
	cout << "Do you have minterms?, Write yes, or no" << endl;

	do {
		while (!(cin >> answer)) {
			cin.clear();
			cin.ignore();
			cout << "INVALID. (yes or no)." << endl;
		}
		if (answer != "yes" && answer != "no") {

			cin.clear();
			cin.ignore();
			cout << "INVALID. write yes or no" << endl;
		}

	} while (answer != "yes" && answer != "no");

	cin.clear();
	cin.ignore();

	if (answer == "no")
		return false;
	else
		return true;

}

bool do_you_have_dontcares()
{

	string answer;
	cout << "Do you have dontcares?, Write yes, or no" << endl;

	do {
		while (!(cin >> answer)) {
			cin.clear();
			cin.ignore();
			cout << "INVALID. (yes or no)." << endl;
		}
		if (answer != "yes" && answer != "no") {

			cin.clear();
			cin.ignore();
			cout << "INVALID. write yes or no" << endl;
		}

	} while (answer != "yes" && answer != "no");

	cin.clear();
	cin.ignore();

	if (answer == "no")
		return false;
	else
		return true;

}

vector<int> takeInput() {
	// To do : put all failures in for loops
	int v;
	int count = 0;
	string s;

	cout << "enter number of variables: ";
	do {
		while (!(cin >> v)) {
			cin.clear();
			cin.ignore();
			cout << "Incorrect. Please enter number of variables again." << endl;
		}
		if (v < 1 || v>16) {
			cin.clear();
			cin.ignore();
			cout << "INVALID. Please enter a valid number (1-16)" << endl;
		}

	} while (v < 1 || v>16);
	int numberOfItems = pow(2, v);
	vector <int> input(numberOfItems, 0);
	string inputStr;
	if (do_u_have_Mins())
	{
		cout << "Please enter the minterms separated by a comma: ";
		cin.ignore();
		getline(cin, inputStr);
		istringstream iss(inputStr);
		//string s;
		while (getline(iss, s, ',')) {
			count++;
			if (atoi(s.c_str()) || (atoi(s.c_str()) == 0)) //to do adjust the isdigit
			{
				if (atoi(s.c_str()) < numberOfItems && count < numberOfItems)
				{
					input[atoi(s.c_str())] = 1;

				}
				else {
					cout << "Please enter a number within range  \n";
					exit(1);
				}
			}
			else
			{
				cout << "Please enter only digits";
				exit(1);
			}

		}
	}
	if (do_you_have_dontcares()) {
		//getline(cin, inputStr);
		//string s;
		cout << "Please enter the dont cares separated by a comma: ";
		getline(cin, inputStr);
		istringstream ivv(inputStr);
		while (getline(ivv, s, ',')) {
			count++;
			if ((atoi(s.c_str()) || (atoi(s.c_str()) == 0)) && (count < numberOfItems)) //to do adjust the isdigit
			{
				if (atoi(s.c_str()) < numberOfItems && count < numberOfItems)
				{

					if (input[atoi(s.c_str())] == 1) {
						cout << "The number was used in the minterms";
						exit(1);
					}
					else
						input[atoi(s.c_str())] = -1;
				}
				else {
					cout << "Please number within range  \n";
					exit(1);
				}
			}
			else
			{
				cout << "Please enter only digits and make sure sum of dont cares and \
            miterms within the range \n";
				exit(1);
			}
		}
	}
	if (!do_u_have_Mins() && !do_you_have_dontcares())
	{
		cout << "funtion will be always equal to" << 0;
	}
	return input;
}

void fillMinTermsDontCaresDict(vector<int> input, map <int, string>& minTerms_dontCares)
{
	string index;
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == 1 || input[i] == -1)
		{
			index = toBinary(i);
			while (index.size() < log2(input.size()))
				index.insert(index.begin(), '0');
			minTerms_dontCares.insert({ i, index });
		}
	}
}

void CheckAdj(string str1, string str2)
{
	int count = 0;
	string combinedString = "";
	for (int i = 0; i < str1.length(); i++)
		if (str1[i] != str1[i])
		{
			combinedString += "-";
			count++;
		}
		else
			combinedString += str1[i];
	if (count > 1)
	{
		exit(1);
	}
	vector <string> col2;
	col2.push_back(combinedString);
	//return combinedString;

}

void calcFirstCol(map <int, string>& minTerms_dontCares, int numberOfVariables) {

	vector <map<int, string>> col1;
	map<int, string>::iterator itr;
	int groupNo;
	for (itr = minTerms_dontCares.begin(); itr != minTerms_dontCares.end(); ++itr)
	{

		groupNo = count(itr->second.begin(), itr->second.end(), '1');
		if (groupNo >= col1.size()) {
			col1.resize(groupNo + 1);
			col1[groupNo].insert({ itr->first, itr->second });
		}
		else {
			col1[groupNo].insert({ itr->first, itr->second });
		}
	}
}

void calsRestCols(vector <map <int, string>>& col1, int size)
{
	map <int, string> ::iterator itr1;
	map <int, string> ::iterator itr2;
	vector <map<string, string>> resultCol;
	// Combination and reduction of implicants
	for (int i = 0; i < size-1; i++) {
		for (itr1 = col1[i].begin(); itr1 != col1[i].end(); itr1++) {
			for (itr2 = col1[i+1].begin(); itr2 != col1[i+1].end(); itr2++)
			{
				if (itr1->first != itr2->first)
					cout << itr1->first << endl;
				//string str = CheckAdj(col1[i].at(j), col1[i + 1].at(k));
			}

		}

	}
}

bool Is_equal(vector <int>v, int var)
{
	for (int i = 0; i < v.size(); i++)
		return (v[i] ^ var);

}

bool isAdjecent(string str1, string str2)
{
	int count = 0;
	for (int i = 0; i < str1.length(); i++)
	{
		if (str1[i] != str2[i])
			count++;
	}
	return (count == 1);
}


void GenPIs(vector <map<int, string>>& col1)
{
	vector<string> PIs;
	map<int, string>::iterator itr;
	int size = col1.size();
	char* checked = new char[size];
}
	//for (int i = 0; i < size; i++)

/*	for (int j = col1[i]->first.begin(); j < col1[i].size(); j++)
	{
		for (int k =j+1; k < size; k++)
		{    
			if (isAdjecent(col1[i], col1[j]))
			{
				checked[i] = '$';
				checked[j] = '$';*/
	

bool existed(vector<int> v, int element, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (v[i] == element)
			return true;
	}
	return false;
}

/*string FromDec2Bin(int n, int size)
{
	string str;
	int len;
	str = bitset<16>(n).to_string();
	len = str.length();
	str = str.erase(0, len - size);
	return str;
}*/

int main()
{
	//  vector <int> input;
	map <int, string> minTerms;
	map <int, string> dontCares;
	map <int, string> minTerms_dontCares;
	vector <map<int, string>> v;
	vector <int> input{ -1,1,1,0 };
	 input = takeInput();
	//fillMinTermsDontCaresDict(input, minTerms_dontCares);
	//calcFirstCol(minTerms_dontCares, log2(input.size()));
	//calsRestCols(v,100);
	//cout << toBinary(500) << endl;
  // cout << Is_equal(input,3);
	return 0;
}
