#include "Ship.h"

Ship::Ship(){}

Ship::Ship(string name, int length) : 
	shipName(name), shipLength(length) {}

Ship::~Ship() {}

void Ship::setBeginning(int row, int col, char ax){
	beginningRow = row;
	beginningCol = col;
	axis = ax;
}

void Ship::setEnding(int row, int col){
	endingRow = row;
	endingCol = col;
}
