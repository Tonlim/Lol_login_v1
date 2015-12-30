/*
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

using std::string;
using std::cout;
using std::cin;

const char magic = 0x11111111;

int main(){
	bool correctPass = false;
	string pass = "";
	string pass2 = "";
	string codedPass = "";

	while (!correctPass){
		//read pass
		cout << "Please provide password:\n";
		char ch;
		const char ENTER = 13;

		while ((ch = _getch()) != ENTER){
			pass += ch;
			std::cout << '*';
		}

		cout << "\nPlease provide the password a second time:\n";
		while ((ch = _getch()) != ENTER){
			pass2 += ch;
			std::cout << '*';
		}

		//check if pass is the same
		if (pass == pass2){
			correctPass = true;
		} 
		else {
			cout << "\nYou made a typo in your password. Please try again.\n\n";
		}
	}

	//encode pass by xor with magic number
	for (char& a : pass){
		codedPass += (char)(a ^ magic);
	}

	//write pass
	std::ofstream file;
	file.open("pass.txt");
	file << codedPass;
	file.close();

	return 0;
}