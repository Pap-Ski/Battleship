#include "cpu.h"

Cpu::Cpu() : Player("cpu")
{
	generateCpuGrid();
	//grid1();
}

Cpu::~Cpu(){};

void Cpu::generateCpuGrid(){
	srand((unsigned)time(0));
	int random = 1 + (rand() % 5);
	
	switch(random){
		case 1:
			grid1();
			break;
		case 2:
			grid2();
			break;
		case 3:
			grid3();
			break;
		case 4:
			grid4();
			break;
		case 5:
			grid5();
			break;
	}
}

void Cpu::grid1(){
	int row,col;
	char axis;
	
		// Patrol Boat
	row = 0; col = 0; axis = 'r';
	placeShipBasedOnAxis(PatrolBoat,row,col,axis);
	
		// Destroyer
	row = 1; col = 0, axis = 'r';
	placeShipBasedOnAxis(Destroyer,row,col,axis);
		
		// Carrier
	row = 2; col = 0, axis = 'r';
	placeShipBasedOnAxis(Carrier,row,col,axis);
		
		// Submarine
	row = 3; col = 0, axis = 'r';
	placeShipBasedOnAxis(Submarine,row,col,axis);
		
		// Battleship
	row = 4; col = 0, axis = 'r';
	placeShipBasedOnAxis(Battleship,row,col,axis);
}

void Cpu::grid2(){
	int row,col;
	char axis;
	
		// Patrol Boat
	row = 2; col = 8; axis = 'd';
	placeShipBasedOnAxis(PatrolBoat,row,col,axis);
	
		// Destroyer
	row = 2; col = 4, axis = 'd';
	placeShipBasedOnAxis(Destroyer,row,col,axis);
		
		// Carrier
	row = 5; col = 9, axis = 'd';
	placeShipBasedOnAxis(Carrier,row,col,axis);
		
		// Submarine
	row = 5; col = 1, axis = 'r';
	placeShipBasedOnAxis(Submarine,row,col,axis);
		
		// Battleship
	row = 8; col = 5, axis = 'r';
	placeShipBasedOnAxis(Battleship,row,col,axis);
}

void Cpu::grid3(){
	int row,col;
	char axis;
	
		// Patrol Boat
	row = 9; col = 3; axis = 'r';
	placeShipBasedOnAxis(PatrolBoat,row,col,axis);
	
		// Destroyer
	row = 3; col = 7, axis = 'r';
	placeShipBasedOnAxis(Destroyer,row,col,axis);
		
		// Carrier
	row = 6; col = 4, axis = 'r';
	placeShipBasedOnAxis(Carrier,row,col,axis);
		
		// Submarine
	row = 5; col = 1, axis = 'd';
	placeShipBasedOnAxis(Submarine,row,col,axis);
		
		// Battleship
	row = 0; col = 5, axis = 'r';
	placeShipBasedOnAxis(Battleship,row,col,axis);
}

void Cpu::grid4(){
	int row,col;
	char axis;
	
		// Patrol Boat
	row = 1; col = 0; axis = 'd';
	placeShipBasedOnAxis(PatrolBoat,row,col,axis);
	
		// Destroyer
	row = 3; col = 4, axis = 'd';
	placeShipBasedOnAxis(Destroyer,row,col,axis);
		
		// Carrier
	row = 5; col = 5, axis = 'r';
	placeShipBasedOnAxis(Carrier,row,col,axis);
		
		// Submarine
	row = 6; col = 9, axis = 'd';
	placeShipBasedOnAxis(Submarine,row,col,axis);
		
		// Battleship
	row = 2; col = 1, axis = 'r';
	placeShipBasedOnAxis(Battleship,row,col,axis);
}

void Cpu::grid5(){
	int row,col;
	char axis;
	
		// Patrol Boat
	row = 9; col = 0; axis = 'r';
	placeShipBasedOnAxis(PatrolBoat,row,col,axis);
	
		// Destroyer
	row = 3; col = 4, axis = 'r';
	placeShipBasedOnAxis(Destroyer,row,col,axis);
		
		// Carrier
	row = 7; col = 2, axis = 'r';
	placeShipBasedOnAxis(Carrier,row,col,axis);
		
		// Submarine
	row = 5; col = 7, axis = 'r';
	placeShipBasedOnAxis(Submarine,row,col,axis);
		
		// Battleship
	row = 1; col = 0, axis = 'r';
	placeShipBasedOnAxis(Battleship,row,col,axis);
}

void Cpu::placeShipBasedOnAxis(Ship &ship, int row, int col, char axis){
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
/*		axis = 'r'
 * ship.setBeginning(row,col,axis);
	for(int x = 1; x <= ship.getLength(); col++,x++)
		playerGrid.setCellData(row,col,ship.getShipSymbol());
	ship.setEnding(row,col-1);
		
		axis = 'l'
	ship.setBeginning(row,col,axis);
	for (int x = 1; x <= ship.getLength(); col--,x++)
		playerGrid.setCellData(row,col,ship.getShipSymbol());
	ship.setEnding(row,col+1);
	
		axis = 'd'
	ship.setBeginning(row,col,axis);
	for(int x = 1; x <= ship.getLength(); row++,x++)
		playerGrid.setCellData(row,col,ship.getShipSymbol());
	ship.setEnding(row-1,col);
	
		axis = 'u'
	ship.setBeginning(row,col,axis);
	for(int x = 1; x <= ship.getLength(); row--,x++)
		playerGrid.setCellData(row,col,ship.getShipSymbol());
	ship.setEnding(row+1,col);
*/
