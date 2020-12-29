#include "Grid.h"
#include <iostream>
using namespace std;

Grid::Grid(){
	for(int i = 0; i < dim; ++i){
		for(int j = 0; j < dim; ++j){
			myGrid[i][j] = ' ';
		}
	}
}

Grid::~Grid(){}

void Grid::displayGrid(){
	cout << "\t  ";
	for(int i = 0; i < dim; ++i)
		cout << i << " ";
	cout << endl;
	//cout << "\t-----------------------------------------" << endl;
	for(char label = 65; label < 75; label++){
		cout << "\t" << label << " ";
		for(int j = 0; j < dim; ++j){
			cout << myGrid[label-65][j] << " ";
		}
		cout << endl;
		//cout << "\t-----------------------------------------" << endl;
	}

	cout << endl;
}

bool Grid::isLabel(char label){
	return (label >= 65 && label <= 75);
}

void Grid::setCellData(int row, int col, char data){
	myGrid[row][col] = data;
}

char Grid::getCellData(int row, int col) const {
	return myGrid[row][col];
}

bool Grid::rangeOccupied(int row, int col, int size, char axis){
	bool occupied = false;
	if(axis == 'r'){
		for(int x = 1; x <= size; x++, col++){
			if(isalpha(myGrid[row][col])){
				occupied = true;
				break;
			}
		}
	} else if(axis == 'l'){
		for(int x = 1; x <= size; x++, col--){
			if(isalpha(myGrid[row][col])){
				occupied = true;
				break;
			}
		}
	} else if(axis == 'd'){
		for(int x = 1; x <= size; x++, row++){
			if(isalpha(myGrid[row][col])){
				occupied = true;
				break;
			}
		}
	} else if(axis == 'u'){
		for(int x = 1; x <= size; x++, row--){
			if(isalpha(myGrid[row][col])){
				occupied = true;
				break;
			}
		}
	}
	/*if(axis == 'h' || axis == 'v'){
		for(int x = 1; x <= size; x++, col++){
			if(isalpha(myGrid[row][col])){
				occupied = true;
				//break;
				return occupied;
			}
		}

		for(int x = 1; x <= size; x++, row++){
			if(isalpha(myGrid[row][col])){
				occupied = true;
				//break;
				return occupied;
			}
		}
	}*/
	return occupied;
}
