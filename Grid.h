#ifndef Grid_H
#define Grid_H
using namespace std;

class Grid{
	private:
		#define dim 10
		//const int dim = 10
		char myGrid[dim][dim];
	
	public:
		Grid();
		~Grid();
		void displayGrid();
		bool isLabel(char label);
		bool rangeOccupied(int row, int col, int size, char dir);
		void setCellData(int row, int col, char data);
		char getCellData(int row, int col) const;
		
};

#endif
