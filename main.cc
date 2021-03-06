#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>

#include "game.h"
#include "slap.h"
#include "floor.h"
#include "slap.h"

using namespace std;

int interpretDir(string dir) {
	if (dir == "nw") return 0;
	else if (dir == "no") return 1;
	else if (dir == "ne") return 2;
	else if (dir == "we") return 3;
	else if (dir == "ea") return 4;
	else if (dir == "sw") return 5;
	else if (dir == "so") return 6;
	else if (dir == "se") return 7;
	else return -1;
}

int main(int argc, char* argv[]) {
	//srand(5);
	srand(time(NULL));
	// setting up file input
	string fileName;
	if (argc == 1) {
		fileName = "default-floor.txt";
	} else if (argc == 2) {
		istringstream fileNameStream{argv[1]};
		fileNameStream >> fileName;
	} else {
		cout << "Incorrect number of arguments" << endl;
		return 1;
	}

	bool restart = false;

	//restart point
	while (true) {
		restart = false;

		// initalialize game
		unique_ptr<Game> current_game;
		ifstream floorPlan;
		floorPlan.exceptions ( std::ifstream::failbit );
		try { floorPlan.open (fileName); }
		catch (std::ifstream::failure e) {
		    cout << "Error in initalializing floor from file name" <<endl;
			return 1;
		}
		// choosing player's race
		while (true) {
			cout << "Welcome to Chamber Crawler 3000!" <<endl;
			cout << "Please enter desired race: " <<endl;
			string race;
			cin >> race;
			if (race == "q") {	// quits the game
				cout << "You have left the game" <<endl;
				return 0;
			} else if ((race == "s") || (race == "d") || (race == "v")
				|| (race == "g") || (race == "t")) {
				current_game = make_unique<Game>(floorPlan, race);
				break;
			} else {
				cout << "Race specified not known. Try again." <<endl;
				continue;
			}
		}
		
		// displaying first floor
		int currFloor = 1;
		current_game->displayFloor(currFloor);
		bool endGame = false;
		bool win = false;
		bool freezeNPCs = false;

		// game starts
		while (true) {
			// check if game should end
			if (endGame) break;
			// player's turn
			cout << "It's your turn. Please enter a command" <<endl;
			string cmd;
			cin >> cmd;
			int dir = interpretDir(cmd);

			// player's action
			if (cmd == "f") {							// stops enemy from moving
				if (freezeNPCs == false) {
					freezeNPCs= true;
				} else {
					freezeNPCs = false;
				}
				current_game->freezeEnemy(freezeNPCs);
				continue;
			} else if (cmd == "r") {	// restarts game
				cout << "Restarting game..." <<endl;
				restart = true;
				break;
			} else if (cmd == "q") {	// quits the game
				cout << "You have left the game" <<endl;
				return 0;
			} else if (cmd == "u") {					// use potion
				cin >> cmd;
				dir = interpretDir(cmd);
				if (dir != -1) {
					try { current_game->pcUse(dir);
					} catch(Slap& errMsg){
						cout<<errMsg.get() <<endl;
						continue;
  					}
				} else {
					cout << "Command not recognized. Try again." <<endl;
					continue;
				}
			} else if (cmd == "a") {						// attack enemy
				cin >> cmd;
				dir = interpretDir(cmd);
				if (dir != -1) {
					try { current_game->pcAtk(dir);
					} catch(Slap& errMsg){
    					cout<<errMsg.get() <<endl;
    					continue;
  					}
				} else {
					cout << "Command not recognized. Try again." <<endl;
					continue;
				}
			} else if (dir != -1) {							// move
				try { current_game->pcMove(dir);
				} catch(Slap& errMsg){
					if (errMsg.get() == "Win") {
						cout << "YOU WIN THE GAME!!!" << endl;
    					cout << "Restart? (y/n) " << endl;
    					char answer;
	    				cin >> answer;
	    				if (answer == 'y') restart = true;
	    				break;
					} else {
	    				cout<<errMsg.get() <<endl;
	    				continue;
    				}
  				}
			} else {
				cout << "Command not recognized. Try again." <<endl;
				continue;
			}

			// NPCs turn
			try { current_game->nextTurn();
			} catch(Slap& errMsg){
				current_game->displayFloor(currFloor);
				cout<<errMsg.get() <<endl;
				return 0;
    		}

    		currFloor = current_game->getCurFloor();
    		current_game->displayFloor(currFloor);
		}

		if (win) {
			
		}

		if (restart) continue;
		break;
	}
}
