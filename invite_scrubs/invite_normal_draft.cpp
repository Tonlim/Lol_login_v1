/*
 * 
 */

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <windows.h>
#include <winuser.h>
#include <conio.h>
#include <string>
#include <fstream>

using namespace std;

const int tick = 75;	//sleep time for before we issue the next command
const string namesFile = "invite_normal_draft_names.txt";
const string variablesFile = "systemvariables_invite_normal_draft.txt";

//system dependent variables
int xOpenInviteScreenStart;
int yOpenInviteScreenStart;
int xOpenInviteScreenSummonersRift;
int yOpenInviteScreenSummonersRift;
int xOpenInviteScreenDraftPick;
int yOpenInviteScreenDraftPick;
int xOpenInviteScreenParty;
int yOpenInviteScreenParty;
int xOpenInviteScreenInvite;
int yOpenInviteScreenInvite;

int xInviteNameBox;
int yInviteNameBox;
int xInviteNameAddList;
int yInviteNameAddList;

int xInviteNormalSquadInvitePlayers;
int yInviteNormalSquadInvitePlayers;


void LeftClick()
{
	INPUT    Input = { 0 };													// Create our input.

	Input.type = INPUT_MOUSE;									// Let input know we are using the mouse.
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;							// We are setting left mouse button down.
	SendInput(1, &Input, sizeof(INPUT));								// Send the input.

	ZeroMemory(&Input, sizeof(INPUT));									// Fills a block of memory with zeros.
	Input.type = INPUT_MOUSE;									// Let input know we are using the mouse.
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;								// We are setting left mouse button up.
	SendInput(1, &Input, sizeof(INPUT));								// Send the input.
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

void ReadSystemVariables(){
	ifstream file;
	file.open(variablesFile);
	string temp;

	getline(file, temp); //comment
	getline(file, temp);
	istringstream(temp) >> xOpenInviteScreenStart;
	getline(file, temp);
	istringstream(temp) >> yOpenInviteScreenStart;
	getline(file, temp); //comment
	getline(file, temp);
	istringstream(temp) >> xOpenInviteScreenSummonersRift;
	getline(file, temp);
	istringstream(temp) >> yOpenInviteScreenSummonersRift;
	getline(file, temp); //comment
	getline(file, temp);
	istringstream(temp) >> xOpenInviteScreenDraftPick;
	getline(file, temp);
	istringstream(temp) >> yOpenInviteScreenDraftPick;
	getline(file, temp); //comment
	getline(file, temp);
	istringstream(temp) >> xOpenInviteScreenParty;
	getline(file, temp);
	istringstream(temp) >> yOpenInviteScreenParty;
	getline(file, temp); //comment
	getline(file, temp);
	istringstream(temp) >> xOpenInviteScreenInvite;
	getline(file, temp);
	istringstream(temp) >> yOpenInviteScreenInvite;
	getline(file, temp); //comment
	getline(file, temp);
	istringstream(temp) >> xInviteNameBox;
	getline(file, temp);
	istringstream(temp) >> yInviteNameBox;
	getline(file, temp); //comment
	getline(file, temp);
	istringstream(temp) >> xInviteNameAddList;
	getline(file, temp);
	istringstream(temp) >> yInviteNameAddList;
	getline(file, temp); //comment
	getline(file, temp);
	istringstream(temp) >> xInviteNormalSquadInvitePlayers;
	getline(file, temp);
	istringstream(temp) >> yInviteNormalSquadInvitePlayers;
}

void OpenInviteScreen(int x, int y){
	SetCursorPos(x - xOpenInviteScreenStart, y + yOpenInviteScreenStart);				//400,150
	Sleep(tick);
	LeftClick();
	SetCursorPos(x - xOpenInviteScreenSummonersRift, y + yOpenInviteScreenSummonersRift);				//400,275
	Sleep(3 * tick);
	LeftClick();
	SetCursorPos(x - xOpenInviteScreenDraftPick, y + yOpenInviteScreenDraftPick);				//200,350
	Sleep(tick);
	LeftClick();
	SetCursorPos(x - xOpenInviteScreenParty, y + yOpenInviteScreenParty);				//200,800
	Sleep(3 * tick);
	LeftClick();
	SetCursorPos(x - xOpenInviteScreenInvite, y + yOpenInviteScreenInvite);				//225,485
	Sleep(750);
	LeftClick();
}


void InviteName(int x, int y, string name){
	SetCursorPos(x - xInviteNameBox, y + yInviteNameBox);				//225,300
	Sleep(tick);
	LeftClick();
	int i = 0;
	for (char& c : name){
		if (islower(c)){
			TypeKey(toupper(c));
		}
		else {
			TypeShiftKey(c);
		}
		i++;
	}
	SetCursorPos(x - xInviteNameAddList, y + yInviteNameAddList);				//50,300
	Sleep(tick);
	LeftClick();
	SetCursorPos(x - xInviteNameBox, y + yInviteNameBox);				//125,300 //same as above!
	Sleep(tick);
	LeftClick();
	for (int j = 0; j < i; j++){
		TypeKey((char)8); //unicode backspace
	}
}

void InviteNormalSquad(){
	HWND window = FindWindow(NULL, "PVP.net Client");
	if (window){
		RECT rect = { 0 };
		GetClientRect(window, &rect);
		SetForegroundWindow(window);
		SetActiveWindow(window);
		SetFocus(window);
		OpenInviteScreen(rect.right, rect.top);
		ifstream input;
		input.open(namesFile);
		string line;
		while (getline(input, line)){
			InviteName(rect.right, rect.top, line);
		}
		SetCursorPos(rect.right - xInviteNormalSquadInvitePlayers, rect.top + yInviteNormalSquadInvitePlayers);		//150,825
		Sleep(tick*3);
		LeftClick();
		input.close();
	}
	else{
		cout << "Couldn't find PVP.net Client";
	}
}

int main(){
	ReadSystemVariables();
	InviteNormalSquad();
	return 0;
}