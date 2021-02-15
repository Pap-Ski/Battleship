#include "Game.h"
#include "Game.cpp"
#include "Player.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
	cout << "\t\t" << string(30,'*') << endl;
	cout << "\t\t*\t" << "   BATTLESHIP" << "\t     *" << endl;
	cout << "\t\t" << string(30,'*') << endl; 
	int mode;
	do{
		cout << "\n\tMODE SELECTION" << endl;
		cout << "\n1. Single Player\n";
		cout << "2. Multiplayer\n";
		cout << "Select a mode: ";
		cin >> mode;
	}while(mode != 1 && mode != 2);
	
	if(mode == 1){
		playerVScpu();
	} else {
		playerVSplayer();
	}

	return 0;
}
