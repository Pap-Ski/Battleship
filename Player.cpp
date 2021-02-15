#include "Player.h"
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

void Player::placeShipBasedOnAxis(Ship &ship, int row, int col, char axis){
	if(axis == 'r'){
		ship.setBeginning(row,col,axis);
		for(int x = 1; x <= ship.getLength(); col++,x++)
			playerGrid.setCellData(row,col,ship.getShipSymbol());
		ship.setEnding(row,col-1);
	} else if(axis == 'd'){
		ship.setBeginning(row,col,axis);
		for(int x = 1; x <= ship.getLength(); row++,x++)
			playerGrid.setCellData(row,col,ship.getShipSymbol());
		ship.setEnding(row-1,col);
	}
}

void Player::grid1(){
	int row,col;
	char axis;
	
		// Patrol Boat
	row = 0; col = 0; axis = 'r';
	placeShipBasedOnAxis(PatrolBoat,row,col,axis);
	
		// Destroyer
	row = 1; col = 9, axis = 'd';
	placeShipBasedOnAxis(Destroyer,row,col,axis);
		
		// Carrier
	row = 5; col = 0, axis = 'r';
	placeShipBasedOnAxis(Carrier,row,col,axis);
		
		// Submarine
	row = 3; col = 0, axis = 'r';
	placeShipBasedOnAxis(Submarine,row,col,axis);
		
		// Battleship
	row = 4; col = 0, axis = 'r';
	placeShipBasedOnAxis(Battleship,row,col,axis);
}

Player::Player(int hah) :
	Destroyer("Destroyer",3),Submarine("Submarine",3),
	PatrolBoat("Patrol Boat",2),Battleship("Battleship",4),
	Carrier("Carrier",5), name("Nii"), secretChar('n'), nOfSunkShips(0),
	hit(false)
{
	grid1();
}

Player::Player() :
	Destroyer("Destroyer",3),Submarine("Submarine",3),
	PatrolBoat("Patrol Boat",2),Battleship("Battleship",4),
	Carrier("Carrier",5), nOfSunkShips(0),hit(false)
{}

Player::Player(string pname) : 
	Destroyer("Destroyer",3),Submarine("Submarine",3),
	PatrolBoat("Patrol Boat",2),Battleship("Battleship",4),
	Carrier("Carrier",5),name(pname),nOfSunkShips(0),hit(false)
{}

Player::~Player(){}

void Player::setupPlayer(){
	cout << "Enter your nickname: ";
	cin >> name;
	cout << "Enter a secret symbol to help access your battleships: ";
	cin >> secretChar;

	cout << "Place your ships in the grid" << endl;
	
	placeShip(PatrolBoat);
	placeShip(Destroyer);
	placeShip(Carrier);
	placeShip(Submarine);
	placeShip(Battleship);
}
/*********************
 * Purpose: Display both player and opponents grids
 * *******************/
void Player::showGrids(){
	showPlayerGrid();
	showOppGrid();
}

void Player::showPlayerGrid(){
	cout << "\n\t" << name << "'s FLEET\n" << endl;
	playerGrid.displayGrid();
	cout << "\t'X' = HIT, 'O' = MISS" << endl;
	cout << "\tConsecutive '-' = SUNK SHIP\n" << endl;
}

void Player::showOppGrid(){
	cout << "\t" << name << "'s ENEMY REFERENCE GRID\n" << endl;
	opponentGrid.displayGrid();
	cout << "\t'X' = HIT, 'O' = MISS" << endl;
	cout << "\tConsecutive '-' = SUNK SHIP\n" << endl;
}

/**********************
 * Fname: placeShip
 * Purpose: To place a ship leftward, rightward, downward or upward
 * ********************/
void Player::placeShip(Ship& ship){
	playerGrid.displayGrid();
	string pos;
	char axis;
	char rowLabel;
	int row;
	int col;

	do{
		cout << "Position your " << ship.getName()
			<< " (takes " << ship.getLength() << " spaces):";
		cin >> pos;
		stringstream ss(pos);
		ss >> rowLabel >> col;
		rowLabel=toupper(rowLabel);
		row = rowLabel-65;

		if(!posIsValid(pos)){
			cout << "Position invalid." << endl;
		} else {
			do{
				cout << "To be placed rightward,leftward,downward or upward[r/l/d/u]?\n";
				cout << "Enter 'p' to reposition ship: ";
				cin >> axis;
				if(axis!='r' && axis!='d' && axis!='l' && axis!='u' && axis!='p'){
					cout << "Wrong input." << endl;
				} else {
					if(axis == 'r'){
						if(playerGrid.rangeOccupied(row,col,ship.getLength(),axis)){
							cout << "Ship collides another."
									<< "Try another position." << endl;
							placeShip(ship);
							break;
						}else if(col+ship.getLength()>10){
							cout << "Row out of range." << endl;
						} else {
							ship.setBeginning(row,col,axis);
							for(int x = 1; x <= ship.getLength(); col++,x++)
								playerGrid.setCellData(row,col,ship.getShipSymbol());
							ship.setEnding(row,col-1);
							break;
						}
					}
					if(axis == 'l'){
						if(playerGrid.rangeOccupied(row,col,ship.getLength(),axis)){
							cout << "Ship collides another."
								<< "Try another position." << endl;
							placeShip(ship);
							break;
						}else if(col-ship.getLength()<-1){
							cout << "Row out of range." << endl;
						} else {
							ship.setBeginning(row,col,axis);
							for (int x = 1; x <= ship.getLength(); col--,x++)
								playerGrid.setCellData(row,col,ship.getShipSymbol());
							ship.setEnding(row,col+1);
							break;
						}
					}
					if(axis == 'd'){
						if(playerGrid.rangeOccupied(row,col,ship.getLength(),axis)){
							cout << "Ship collides another."
									<< "Try another position." << endl;
							placeShip(ship);
							break;
						}else if(row+ship.getLength()>10){
							cout << "Column out of range." << endl;
						} else {
							ship.setBeginning(row,col,axis);
							for(int x = 1; x <= ship.getLength(); row++,x++)
								playerGrid.setCellData(row,col,ship.getShipSymbol());
							ship.setEnding(row-1,col);
							break;
						}
					}
					if(axis == 'u'){
						if(playerGrid.rangeOccupied(row,col,ship.getLength(),axis)){
							cout << "Ship collides another."
									<< "Try another position." << endl;
							placeShip(ship);
							break;
						}else if(row-ship.getLength()<-1){
							cout << "Column out of range." << endl;
						} else {
							ship.setBeginning(row,col,axis);
							for(int x = 1; x <= ship.getLength(); row--,x++)
								playerGrid.setCellData(row,col,ship.getShipSymbol());
							ship.setEnding(row+1,col);
							break;
						}
					}
					if(axis=='p'){
						clearScreen();
						placeShip(ship);
						break;
					}
				}
			} while(axis!='r' || axis!='d' || axis!='l' || axis!='u'||
			(axis == 'd' && row+ship.getLength()>10) ||
			(axis == 'u' && row-ship.getLength()<-1) ||
			(axis == 'r' && col+ship.getLength()>10) ||
			(axis == 'l' && col-ship.getLength()<-1));
		}
	} while (!posIsValid(pos));
	clearScreen();
	clearScreen();
	cout << ship.getName() << " ready!" << endl;
}

/**************
 * Fname: posIsValid
 * Purpose: Check validity of chosen position
 * ************/
bool Player::posIsValid(string pos){
	char rowLabel;
	int col;
	stringstream ss(pos);
	ss >> rowLabel >> col;
	rowLabel=toupper(rowLabel);

	if(pos.size() < 2 || col > 9 || col < 0 || !playerGrid.isLabel(rowLabel)){
		return false;
	} else {
		return true;
	}
}

/**********
 * Fname: modifyPlayerGrid
 * Purpose: insert a character into the player grid
 * *************/
void Player::modifyPlayerGrid(int row, int col, char data){
	playerGrid.setCellData(row, col, data);
}

/*********
 * Fname: modifyOppGrid
 * Purpose: insert a character into the opponent grid
 * *********/
void Player::modifyOppGrid(int row, int col, char data){
	opponentGrid.setCellData(row, col, data);
}

void clearScreen(){
	#ifdef WINDOWS
		system("cls");
	#else
		system("clear");
	#endif
}
