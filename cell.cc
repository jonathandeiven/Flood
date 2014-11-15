#include <iostream>
#include "grid.h"
#include "cell.h"
#include "textdisplay.h"
#include "window.h"

using namespace std;

void Cell::setCoords(int r, int c, int x, int y, int width, int height, Xwindow *w){
	this->r = r;
	this->c = c;
	this->x = x;
	this->y = y;
	this->height = height;
	this->width = width;
	this->window = w;
}

void Cell::draw(){ //Will draw in a colour for each state
	switch(this->state){ //Different colour based on state
		case 0:{
			(this->window)->fillRectangle(this->x, this->y, this->width, this->height, Xwindow::White);
			break;
		}

		case 1:{
			(this->window)->fillRectangle(this->x, this->y, this->width, this->height, Xwindow::Black);
			break;
		}

		case 2:{
			(this->window)->fillRectangle(this->x, this->y, this->width, this->height, Xwindow::Red);
			break;
		}

		case 3:{
			(this->window)->fillRectangle(this->x, this->y, this->width, this->height, Xwindow::Green);
			break;
		}

		case 4:{
			(this->window)->fillRectangle(this->x, this->y, this->width, this->height, Xwindow::Blue);
			break;
		}

		default:
			break;
	}	
}


void Cell::notifyDisplay(){ //Send state to Text Display
	/*Since state will always be a single integer, 0 to 4, we 
	  can convert as below using ASCII value of '0'. */
	char ch_State;

	if ( this->state == 0 ) { ch_State = '0'; } 
	//handles weird issue with 0 converting to '\000'
	else { ch_State = this->state + '0'; }

	(this->td)->notify(this->r, this->c, ch_State);
}

Cell::Cell(){ //default constructor
	this->state = 0;
	this->prevState = 0;
	this->numNeighbours = 0;
	this->r = 0;
	this->c = 0;
	this->x = 0;
	this->y = 0;
	this->height = 0;
	this->width = 0;
	this->td = NULL;
	this->window = NULL;
}

int Cell::getState(){ //state accessor method
	return this->state;
}

void Cell::setState(const int& change){ //state mutator method
	this->prevState = this->state; //set previous state
	this->state = change; //set new state
	this->notifyDisplay(); //tell display to change its state accordingly
	this->draw();
}

void Cell::setDisplay(TextDisplay* t){ //Display mutator method
	this->td = t;
}

void Cell::addNeighbour(Cell *neighbour){ //Add a neighbour
	if (numNeighbours < maxNeighbours)
		this->neighbours[numNeighbours++] = neighbour;
}

void Cell::notify( const int & change){
	this->setState(change); //Call setState for this (0,0) Cell object

	for(int i = 0; i < this->numNeighbours; i++) //Notify all neighbours
		(this->neighbours[i])->notify(this->state, this->prevState);
}

void Cell::notify(const int & current, const int & previous){
	if( this->state == previous ){
		this->prevState = previous;
		this->state = current;
		this->draw();

		/*Recursively notify all neighbouring cells. If there is any cell that
		  needs to change state as well, it will.*/
		for( int i = 0; i < this->numNeighbours; i++)
			(this->neighbours[i])->notify(this->state, this->prevState);

		this->notifyDisplay(); //Notify Text Display of all changes
	}
}

