#ifndef SHIP_H
#define SHIP_H
#include <iostream>
using namespace std;

class Ship{
	private:
		string shipName;
		char axis;
		int shipLength;
	public:
		Ship();
		Ship(string, int);
		~Ship();
			// Accessors
		int getLength() const {return shipLength;}
		char getAxis() const {return axis;}
		string getName() const {return shipName;}
		char getShipSymbol() const {return shipName[0];}
		
			// Others
		bool hasSunk = false;
		void setBeginning(int, int,char);
		void setEnding(int, int);
		int beginningRow, beginningCol;
		int endingRow, endingCol;
		/*int getBeginningRow() const {return beginningRow;}
		int getBeginningCol() const {return beginningCol;}
		int getEndingRow() const {return endingRow;}
		int getEndingCol() const {return endingCol;}*/
};
#endif
