#include "Game.h"
#include "Game.cpp"
#include "Player.h"
#include <iostream>
using namespace std;

int main()
{
	cout << "\t\t*****PLAYER 1*****\n";
	Player p1;
	cout << "\t\t*****PLAYER 1 READY*****\n";
	system("clear");
	cout << "\t\t*****PLAYER 2*****\n";
	Player p2;
	cout << "\t\t*****PLAYER 2 READY*****\n";

	cout << "\nPlayers ready, and all ships postioned!" << endl;
	cout << p1.getName() << " will begin." << endl;

	while(!gameOver){
		shoot(p1, p2);
		if(gameOver)
			break;
		shoot(p2, p1);
	}

	return 0;
}
