#include <iostream>
#include "grid.h"
#include "cell.h"
#include "textdisplay.h"
#include "window.h"

using namespace std;

void Grid::clearGrid(){ //Clears the grid
	if ( this->gridSize > 0 ){ //Ensures grid was initalized before
		for (int i = 0; i < this->gridSize; i++){
			delete []this->theGrid[i];
			this->theGrid[i] = NULL;
		}

		delete [] this->theGrid;
		theGrid = NULL;
		delete this->td;
		this->td = NULL;
		delete this->theWindow;
		theWindow = NULL;
	}
}

Grid::Grid(){ //Default constructor
	this->theGrid = NULL;
	this->gridSize = 0;
	this->td = NULL;
	this->theWindow = NULL;
}

Grid::~Grid(){ //Destructor
	this->clearGrid(); 
}

bool Grid::isWon(){
	return (this->td)->isFilled(); //Return win status
}

void Grid::init(int n){
	this->clearGrid();  //If non-empty, destroys grid

	//Height and width of each cell	
	int height, width;
	height =  500 / n;
	width = 500 / n;

	this->theGrid = new Cell*[n]; //Create new grid of size n x n
	this->td = new TextDisplay(n); //new Text Display 
	this->theWindow = new Xwindow; //new Window Display

	for (int i = 0; i < n; i++){
		this->theGrid[i] = new Cell[n];
		for(int j = 0; j < n; j++){ //Cell initializations
			(this->theGrid[i][j]).setDisplay(this->td); //set display
			(this->theGrid[i][j]).setCoords(i, j, i*width, j*height, width, height, theWindow); //set co-ordinates
			(this->theGrid[i][j]).setState(0); //default state
		}
	}

	this->gridSize = n; //set gridSize field to inputted grid size

	//Set Neighbours
	for (int r = 0; r < n; r++){
		for (int c = 0; c < n; c++){
			int left = r - 1;
			int right = r + 1;
			int top = c - 1;
			int bottom = c + 1;

			//Set left neighbour
			if ( !(left == 0 && c == 0) && left > -1 ){
				Cell* neighbour = &(this->theGrid[left][c]);
				(this->theGrid[r][c]).addNeighbour(neighbour);
			}

			//Set right neighbour
			if ( right < n ){
				Cell* neighbour = &(this->theGrid[right][c]);
				(this->theGrid[r][c]).addNeighbour(neighbour);
			}

			//Set top neighbour
			if ( !(r == 0 && top == 0) && top > -1 ){
				Cell* neighbour = &(this->theGrid[r][top]);
				(this->theGrid[r][c]).addNeighbour(neighbour);
			}

			//Set bottom neighbour
			if ( bottom < n ){
				Cell* neighbour = &(this->theGrid[r][bottom]);
				(this->theGrid[r][c]).addNeighbour(neighbour);
			}
		}
	}
}

void Grid::change(const int & state){  //Notify (0,0) of new state
	(this->theGrid[0][0]).notify(state);
}

void Grid::init(int r, int c, int state){
	//Check for valid input
	if ( r >= 0 && r <= (this->gridSize - 1) && c >= 0 && c <= (this->gridSize - 1) )
		(this->theGrid[r][c]).setState(state); //sets state of (r,c) to state
}

ostream& operator<<(ostream &out, const Grid& g){ //overload << operator for grid
	out << *(g.td);
	return out; //cascade << operator
}
