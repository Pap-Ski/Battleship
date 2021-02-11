#ifndef CPU_H
#define CPU_H
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Player.h"
#include "Player.cpp"

class Cpu : public Player{
	private:
		void grid1();
		void grid2();
		void grid3();
		void grid4();
		void grid5();
		void placeShipBasedOnAxis(Ship &ship, int row, int col, char axis);
		void generateCpuGrid();
		
	public:
		Cpu();
		~Cpu();
		
};



#endif
