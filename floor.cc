#include "floor.h"
#include "display.h"
#include "npc.h"
#include "pc.h"
#include "potion.h"
#include "gold.h"
#include "chamber.h"
#include "tile.h"
#include "basictile.h"
#include "tiledecorator.h"
#include "passage.h"
#include "stairs.h"
#include "door.h"
#include "wall.h"
#include "none.h"
#include <vector>

using namespace std;

// constructor and destructors
Floor::Floor(int position) :
	st{make_shared<Stairs>()}, player{make_shared<PC>()}, 
	position{position}, d{make_shared<Display>()}, 
	maxPotion{10}, maxEnemy{20} {
	d->setFloor(this);
}

Floor::~Floor() {}

// accessors and mutators
shared_ptr<Chamber> & Floor::getChamber(int index) {
	return chambers[index];
}

shared_ptr<Tile> & Floor::getTile(int x, int y) {
	return tiles[x][y];
}

shared_ptr<Stairs> & Floor::getStairs(int index) {
	return st;
}

shared_ptr<NPC> & Floor::getNPC(int index) {
	return enemies[index];
}

shared_ptr<Potion> & Floor::getPotion(int index) {
	return potions[index];
}

shared_ptr<Gold> & Floor::getGold(int index) {
	return treasure[index];
}

shared_ptr<PC> & Floor::getPlayer() {
	return player;
}

int Floor::getPosition() {
	return position;
}

Display & Floor::getDisplay() const {
	return *d;
}

// other methods
void Floor::constructFloor() {
	// not sure if this is needed
}

void Floor::constructObject(int x, int y, char input) {
	if (input == '@') {

	} else if (input == 'H') {

	} else if (input == 'W') {

	} else if (input == 'E') {

	} else if (input == 'O') {

	} else if (input == 'M') {

	} else if (input == 'D') {

	} else if (input == 'L') {

	} else if (input == 'P') {

	} else if (input == 'G') {

	} else if (input == 92) {
		tiles[x][y] = make_shared<BasicTile> (x, y, d);
	}
}

void Floor::constructFloor(istream &input, int start) {
	string line;

	// looping to the correct starting line
	for (int i = 0; i < start - 1; ++i) {
		input.ignore(79,'\n');
	}

	// construct all Tiles accordingly
	tiles.resize(25);
	for (int i = 0; i < 25; ++i) {
		tiles[i].resize(79);
		getline(input, line);
		for (int j = 0; j < 79; ++i) {
			if (line[i] == '|') {
				tiles[i][j] = make_shared<Wall> ((make_shared<BasicTile> (i, j, d)), 1);
			} else if (line[i] == ' ') {
				tiles[i][j] = make_shared<None> ((make_shared<BasicTile> (i, j, d)));
			} else if (line[i] == '-') {
				tiles[i][j] = make_shared<Wall> ((make_shared<BasicTile> (i, j, d)), 0);
			} else if (line[i] == '#') {
				tiles[i][j] = make_shared<Passage> ((make_shared<BasicTile> (i, j, d)));
			} else if (line[i] == '+') {
				tiles[i][j] = make_shared<Door> ((make_shared<BasicTile> (i, j, d)));
			} else {
				Floor::constructObject(i, j, line[i]);
			}
		}
	}

	// setting up neigbours for all Tiles
	for (int i = 0; i < 25; ++i) {
		for (int j = 0; j < 79; ++j) {
			// the neighbours can be identified by position in the vector (integer 0-9 inclusive)
			if (i - 1 < 0 && j - 1 < 0) {
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(tiles[i][j + 1]);
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(tiles[i + 1][j]);
				tiles[i][j]->addNeighbr(tiles[i + 1][j + 1]);
			} else if (i - 1 < 0 && j + 1 > 78) {
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(tiles[i][j - 1]);
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(tiles[i + 1][j - 1]);
				tiles[i][j]->addNeighbr(tiles[i + 1][j]);
				tiles[i][j]->addNeighbr(make_shared<Tile>());
			} else if (i - 1 < 0) {
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(tiles[i][j - 1]);
				tiles[i][j]->addNeighbr(tiles[i][j + 1]);
				tiles[i][j]->addNeighbr(tiles[i + 1][j - 1]);
				tiles[i][j]->addNeighbr(tiles[i + 1][j]);
				tiles[i][j]->addNeighbr(tiles[i + 1][j + 1]);
			} else if (i + 1 > 24 && j - 1 < 0) {
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(tiles[i - 1][j]);
				tiles[i][j]->addNeighbr(tiles[i - 1][j + 1]);
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(tiles[i][j + 1]);
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(make_shared<Tile>());
			} else if (i + 1 > 24 && j + 1 > 78) {
				tiles[i][j]->addNeighbr(tiles[i - 1][j - 1]);
				tiles[i][j]->addNeighbr(tiles[i - 1][j]);
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(tiles[i][j - 1]);
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(make_shared<Tile>());
			} else if (i + 1 > 24) {
				tiles[i][j]->addNeighbr(tiles[i - 1][j - 1]);
				tiles[i][j]->addNeighbr(tiles[i - 1][j]);
				tiles[i][j]->addNeighbr(tiles[i - 1][j + 1]);
				tiles[i][j]->addNeighbr(tiles[i][j - 1]);
				tiles[i][j]->addNeighbr(tiles[i][j + 1]);
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(make_shared<Tile>());
			} else if (j - 1 < 0) {
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(tiles[i - 1][j]);
				tiles[i][j]->addNeighbr(tiles[i - 1][j + 1]);
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(tiles[i][j + 1]);
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(tiles[i + 1][j]);
				tiles[i][j]->addNeighbr(tiles[i + 1][j + 1]);
			} else if (j + 1 > 78) {
				tiles[i][j]->addNeighbr(tiles[i - 1][j - 1]);
				tiles[i][j]->addNeighbr(tiles[i - 1][j]);
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(tiles[i][j - 1]);
				tiles[i][j]->addNeighbr(make_shared<Tile>());
				tiles[i][j]->addNeighbr(tiles[i + 1][j - 1]);
				tiles[i][j]->addNeighbr(tiles[i + 1][j]);
				tiles[i][j]->addNeighbr(make_shared<Tile>());
			} else {
				tiles[i][j]->addNeighbr(tiles[i - 1][j - 1]);
				tiles[i][j]->addNeighbr(tiles[i - 1][j]);
				tiles[i][j]->addNeighbr(tiles[i - 1][j + 1]);
				tiles[i][j]->addNeighbr(tiles[i][j + 1]);
				tiles[i][j]->addNeighbr(tiles[i][j + 1]);
				tiles[i][j]->addNeighbr(tiles[i + 1][j - 1]);
				tiles[i][j]->addNeighbr(tiles[i + 1][j]);
				tiles[i][j]->addNeighbr(tiles[i + 1][j + 1]);
			}
		}
	}
}

std::ostream & operator<<(ostream &out, const Floor &f) {
	out << f.getDisplay();
	return out;
}
