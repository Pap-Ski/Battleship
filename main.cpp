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
	
	int mainMenuOption;
	do{
		cout << "\n\tMAIN MENU" << endl;
		cout << "\n1. Play Game\n";
		cout << "2. How to Play\n";
		cout << "Select an option: ";
		cin >> mainMenuOption;
		
		if(mainMenuOption == 1){
			playGame();
		}else if(mainMenuOption == 2){
			howToPlay();
		}
	}while(mainMenuOption != 1 && mainMenuOption != 2);
	
	

	return 0;
}
