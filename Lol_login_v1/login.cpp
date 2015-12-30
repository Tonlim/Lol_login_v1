/*
 * 
 */

#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <winuser.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <stdlib.h>

using std::string;
using std::cout;

const char magic = 0x11111111;			//used to decode password

void LeftClick()
{
	INPUT Input = { 0 };										// Create our input.

	Input.type = INPUT_MOUSE;									// Let input know we are using the mouse.
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;					// We are setting left mouse button down.
	SendInput(1, &Input, sizeof(INPUT));						// Send the input.

	ZeroMemory(&Input, sizeof(INPUT));							// Fills a block of memory with zeros.
	Input.type = INPUT_MOUSE;									// Let input know we are using the mouse.
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;						// We are setting left mouse button up.
	SendInput(1, &Input, sizeof(INPUT));						// Send the input.
}

void TypeKey(int vk) {

	KEYBDINPUT  kb = { 0 };
	INPUT       Input = { 0 };

	/* Generate a "key down" */
	kb.wVk = vk;
	Input.type = INPUT_KEYBOARD;
	Input.ki = kb;
	SendInput(1, &Input, sizeof(Input));

	/* Generate a "key up" */
	ZeroMemory(&kb, sizeof(KEYBDINPUT));
	ZeroMemory(&Input, sizeof(INPUT));
	kb.dwFlags = KEYEVENTF_KEYUP;
	kb.wVk = vk;
	Input.type = INPUT_KEYBOARD;
	Input.ki = kb;
	SendInput(1, &Input, sizeof(Input));
}

void TypeShiftKey(int vk){
	KEYBDINPUT  kb = { 0 };
	INPUT       Input = { 0 };

	/* Generate a "key down" */
	kb.wVk = VK_SHIFT;
	Input.type = INPUT_KEYBOARD;
	Input.ki = kb;
	SendInput(1, &Input, sizeof(Input));
	TypeKey(vk);
	/* generate a "key up"*/
	ZeroMemory(&kb, sizeof(KEYBDINPUT));
	ZeroMemory(&Input, sizeof(INPUT));
	kb.dwFlags = KEYEVENTF_KEYUP;
	kb.wVk = VK_SHIFT;
	Input.type = INPUT_KEYBOARD;
	Input.ki = kb;
	SendInput(1, &Input, sizeof(Input));
}

void StartUpLoL(){
	system("C:\\\"Riot Games\"\\\"League of Legends\"\\lol.launcher.exe");
	//Lol patcher
}

void Login(){
	HWND window = FindWindow(NULL, "PVP.net Client");
	while (!window){
		Sleep(2500);
		window = FindWindow(NULL, "PVP.net Client");
	}
	RECT rect = {0};
	GetClientRect(window,&rect);
	SetForegroundWindow(window);
	SetActiveWindow(window);
	SetFocus(window);
	SetCursorPos(rect.right - 750, rect.top + 415);	//415:pass  355:name
	Sleep(50);
	LeftClick();
	Sleep(50);
	
	//read coded pass
	std::ifstream file;
	file.open("pass.txt");
	string codedPass;
	string pass = "";
	file >> codedPass;

	//decode pass by xor with magic number
	for (char& a : codedPass){
		pass += (char)(a ^ magic);
	}

	//string pass = "Heusden0";
	for (char& c : pass){
		if (islower(c)){
			TypeKey(toupper(c));
		}
		else {
			TypeShiftKey(c);
		}
	}
	
	SetCursorPos(rect.right - 750, rect.top + 445);	//goto login button
	Sleep(50);
	LeftClick();

}

void LaunchLoL(){
	HWND window = FindWindow(NULL, "LoL Patcher");
	while (!window){
		Sleep(2500);
		window = FindWindow(NULL, "LoL Patcher");
	}
	RECT rect = { 0 };
	GetClientRect(window, &rect);
	SetForegroundWindow(window);
	SetActiveWindow(window);
	SetFocus(window);
	//wait untill the patcher is ready
	Sleep(1500);		
	SetCursorPos(rect.right + 700, rect.top + 100);
	Sleep(50);	
	LeftClick();
	Login();
}

int main(){
	StartUpLoL();
	LaunchLoL();
	return 0;
}