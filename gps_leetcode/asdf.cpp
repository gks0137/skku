#include <iostream>
#include <string>
using namespace std;

//This function convert input to secret string and prints it.
//string target : Original input string
//int num : indicates number of secret characters
void printSecretStr(string target, int num){
	for (int i = 0; i < target.size(); i++) {
		if (i >= num && target[i] != ' ') {
			cout << '*';
		} else {
			cout << target[i];
		}
	}
	cout << endl;
}

//Receive input from user
//Receive input from user
bool customInput(string& str, int& num){
	num = 0;
	char c = getchar();
	while ('0' <= c && c <= '9') {
		num *= 10;
		num += c - '0';
		c = getchar();
	}
	if (c != '$') {
		cout << "Incorrect Number!" << endl;
		return false;
	}
	while ((c = getchar()) != '\n') {
		str.push_back(c);
	}
	if (str.size() < num) {
		cout << "String is too short" << endl;
		return false;
	}
	return true;
}
int main()
{
	//stores user input
	string str; 
	
	//stores number of secrete characters
	int num; 

	if(customInput(str,num)){  
		printSecretStr(str,num);
	}
	return 0;
}