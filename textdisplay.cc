#include <iostream>
#include "grid.h"
#include "cell.h"
#include "textdisplay.h"

using namespace std;

TextDisplay::TextDisplay(int n): gridSize(n) { //Default constructor
	this->theDisplay = new char*[n];
	for (int i = 0; i < n; i++){
		this->theDisplay[i] = new char[n];
		for (int j = 0; j < n; j++)
			this->theDisplay[i][j] = '0'; //Initialize to default state
	}
	/*Initialize colour count of 0 to be the number of cells in 
	  the grid, because every cell is initialized to 0. */
	colourCount[0] = gridSize*gridSize;

	/*We should initialize all other array elements to be 0 at
	  initialization. Since there's only 4, there's no need to
	  do a for loop. If more states, then replaced with loop.*/
	colourCount[1] = 0;
	colourCount[2] = 0;
	colourCount[3] = 0;
	colourCount[4] = 0;
}

void TextDisplay::notify(int r, int c, char ch){
	char prevState = this->theDisplay[r][c]; //get previous state 
	char newState = ch;
	int prevColourIndex = prevState - '0'; //Convert char to int
	int newColourIndex = newState - '0';

	//fixes weird issue with 0 converting to int
	if ( prevState == '0') { prevColourIndex = 0; }
	if ( newState == '0' ) { newColourIndex = 0;  }
	
	this->theDisplay[r][c] = ch; //set new state

	this->colourCount[prevColourIndex]--; //Update colour table
	this->colourCount[newColourIndex]++;
}

bool TextDisplay::isFilled(){
	unsigned int numGrids = this->gridSize * this->gridSize; //number of grids in grid
	int numStates = 5;
	/*Since the array colourCount is really small, we can simply
	  use a linear search. */
	for (int i = 0; i < numStates; i++)
		if ( this->colourCount[i] == numGrids )
			return true; //One colour fills all grids

	return false; //Can't find any colour that fills all grids
}

TextDisplay::~TextDisplay(){ //Default destructor
	for (int i = 0; i < this->gridSize; i++)
		delete[] this->theDisplay[i];

	delete[] this->theDisplay;
}

ostream& operator<<(ostream &out, const TextDisplay& td){
	for (int row = 0; row < td.gridSize; row++){
		for (int col = 0; col < td.gridSize; col++)
			out << td.theDisplay[row][col]; //print all columns in row
		out << endl; //new line for every row
	}

	return out; //facilitate cascading of << operator
}
