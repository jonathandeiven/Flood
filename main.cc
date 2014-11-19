#include <iostream>
#include <fstream>
#include <sstream>

#include "cell.h"
#include "grid.h"
#include "textdisplay.h"

using namespace std;

int main(){

	string command;
	Grid* game = NULL; //game grid
	int movesLeft = 0; //track # moves left
	bool boardExists = false; //true is there is a board
	bool gameStatus = false; //true if game has started
	bool initializedBoard = false; //true if board is initialized
	bool inputExhausted = false; //Check to see if input is exhausted
	int n; //Size of game board

	srand(time(NULL)); //Randomize seed

	while (true) {

		//Break if ran out of moves
		if ( gameStatus == true && movesLeft == 0 ) { break; }

		//Case for when game begins with uninitialized board (Auto-Win)
		if ( gameStatus == true && initializedBoard == false) { break; }
		
		//Check if game is won
		if ( gameStatus == true){
			//Can only check if game status is running
			if ( game->isWon() ) { break; }
		}

		cin >> command;

		if ( cin.eof() ) { inputExhausted = true; break; }

		if (command == "new" && gameStatus == false){
			cin >> n; // n x n grid
			if(n < 1) { continue; } //cannot initialize <1
			if(!game) game = new Grid; //Create only if doesn't exist
			game->init(n); // create grid
			boardExists = true;
		}

		else if (command == "random" && boardExists == true){
			/*Nested for-loop is O(n^2) => Very slow. Working on 
			code enhancements here.*/
			for (int r = 0; r < n; r++){
				for (int c = 0; c < n; c++){
					int state = rand() % 5;
					game->init(r, c, state);
				}
			}
		cout << *game; //display the board
		initializedBoard = true;
		}

		else if (command == "init" && boardExists == true){
			int r, c, state;
			while( cin >> r >> c ){

				if (r == -1 || c  == -1 ){ break; } //Exit init mode
				else{
					cin >> state;
					if( state < 0 || state > 4 ) { continue; } 
					//ignore invalid state
					game->init(r, c, state);
				}
			}
			cout << *game; //display the board
			initializedBoard = true;
		}

		else if (command == "-1"){
			continue; //ignore -1 input unless in init mode
		}

		else if (command == "include" && boardExists == true){
			string filename;
			cin >> filename;

			ifstream file(filename.c_str()); //Open file
			if( file.fail() ) { break; } //Exit if open failed
 			int r, c, state;
			while( file >> r >> c ){
				if ( (r == -1 || c  == -1 ) || file.eof() ) { break; }
				//-1 -1 or EOF signals end of include command
				else{

					file >> state;
					if( state < 0 || state > 4 ) { continue; } 
					//ignore invalid state
					game->init(r, c, state);
				}
			}
			initializedBoard = true;
			cout << *game; //display the board
		}

		else if (command == "game" && gameStatus == false && game ){
			int g; //g moves
			cin >> g;

			if (g == 1) { cout << "1 move left" << endl; }
			else { cout << g << " moves left" << endl; }

			movesLeft = g;
			gameStatus = true;
		}

		else if (command == "switch" && gameStatus == true){
			int s; //state to change (0,0) to
			cin >> s;

			game->change(s);
			movesLeft--;

			cout << *game;
			if (movesLeft == 1) { cout << "1 move left" << endl; }
			else { cout << movesLeft << " moves left" << endl; }
		}

		else if (command == "?"){
			cout << "White: 0" << endl;
			cout << "Black: 1" << endl;
			cout << "Red:   2" << endl;
			cout << "Green: 3" << endl;
			cout << "Blue   4" << endl;
		}

		else{
			continue; //Ignore all other input
		}
	}

	//Case for legitimate win and for uninitialized board "auto-win"
	if( !inputExhausted ){
		if (  game->isWon() || initializedBoard == false ) 
			cout << "Won" << endl;
		else
			cout << "Lost" << endl;
	}

	gameStatus = false;   //game done
	if(game) delete game; //delete only if exists
}

