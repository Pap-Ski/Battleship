#ifndef Player_H
#define Player_H
#include "Grid.h"
#include "Grid.cpp"
#include "Ship.h"
#include "Ship.cpp"

class Player{
	protected:
		Grid playerGrid;
		Grid opponentGrid;
		Ship Destroyer,Submarine,PatrolBoat,Battleship,Carrier;
		string name;
		char secretChar;
		int nOfSunkShips;
		bool hit;

	public:
		Player();
		Player(int hah); // for test purposes
		Player(string pname); // specifically for cpu constructor
		~Player();
			// Accessors
		void setupPlayer();
		string getName() const {return name;}
		char getSecretChar() const {return secretChar;}
		int getnOfSunkShips() const {return nOfSunkShips;}
		Grid getOpponentGrid() const {return opponentGrid;}
		Grid getPlayerGrid() const {return playerGrid;}
		Ship& getDestroyer() {return Destroyer;}
		Ship& getSubmarine() {return Submarine;}
		Ship& getPatrolBoat() {return PatrolBoat;}
		Ship& getBattelship() {return Battleship;}
		Ship& getCarrier() {return Carrier;}
		
			// Others
		void placeShip(Ship&);
		void showGrids();
		void showPlayerGrid();
		void showOppGrid();
		bool posIsValid(string pos);
		void incnOfSunkShips() {nOfSunkShips++;}
		void modifyPlayerGrid(int row, int col, char data);
		void modifyOppGrid(int row, int col, char data);
		bool isHit() {return hit;}
		void setHit(bool x) {hit = x;}
		
		//  test fxns
		void grid1();
		void placeShipBasedOnAxis(Ship &ship, int row, int col, char axis);		
};
#endif

void clearScreen();
