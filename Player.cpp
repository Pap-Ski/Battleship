#include "Player.h"
#include <sstream>
#include <iostream>
using namespace std;

Player::Player() :
	Destroyer("Destroyer",3),Submarine("Submarine",3),
	PatrolBoat("Patrol Boat",2),Battleship("Battleship",4),
	Carrier("Carrier",5), nOfSunkShips(0)
{
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

/*Player::Player(string pname) :
Destroyer("Destroyer",3),Submarine("Submarine",3),
	PatrolBoat("Patrol Boat",2),Battleship("Battleship",4),
	Carrier("Carrier",5), name(pname), nOfSunkShips(0)
{
	PatrolBoat.setBeginning(0,0,'h');
	playerGrid.setCellData(0,0,'P');
	playerGrid.setCellData(0,1,'P');
	PatrolBoat.setEnding(0,1);
	Battleship.setBeginning(1,0,'h');
	playerGrid.setCellData(1,0,'B');
	playerGrid.setCellData(1,1,'B');
	playerGrid.setCellData(1,2,'B');
	playerGrid.setCellData(1,3,'B');
	Battleship.setEnding(1,3);
	Destroyer.setBeginning(2,0,'h');
	playerGrid.setCellData(2,0,'D');
	playerGrid.setCellData(2,1,'D');
	playerGrid.setCellData(2,2,'D');
	Destroyer.setEnding(2,2);//3
	Submarine.setBeginning(0,6,'v');
	playerGrid.setCellData(0,6,'S');
	playerGrid.setCellData(1,6,'S');
	playerGrid.setCellData(2,6,'S');
	Submarine.setEnding(2,6);// 3
	Carrier.setBeginning(4,0,'h');
	playerGrid.setCellData(4,0,'-');
	playerGrid.setCellData(4,1,'-');
	playerGrid.setCellData(4,2,'-');
	playerGrid.setCellData(4,3,'-');
	playerGrid.setCellData(4,4,'-');
	Carrier.setEnding(4,4);// 5
}*/

Player::~Player(){}

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
	cout << "\t'-' = Part of ship is hit\n" << endl;
}

void Player::showOppGrid(){
	cout << "\t" << name << "'s ENEMY REFERENCE GRID\n" << endl;
	opponentGrid.displayGrid();
	cout << "\t'X' = HIT, 'O' = MISS" << endl;
	cout << "\tConsecutive '#' = SUNK SHIP\n" << endl;
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
						system("clear");
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
	system("clear");
	system("clear");
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
