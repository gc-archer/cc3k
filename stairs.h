#ifndef _STAIRS_H_
#define _STAIRS_H_

#include "tiledecorator.h"

class Stairs: public TileDecorator {

public:
	// constructor and destructor
	Stairs(shared_ptr<BasicTile> base);
	~Stairs();

	// accessors and mutators
	shared_ptr<Object> *& getObject(int index) override;
	shared_ptr<Tile> *& getNeighbr(int index) override;

	// other methods
	void addObject(shared_ptr<Object> o) override;
	void addNeighbr(shared_ptr<Tile> t) override;
	void killObject() override;
	void moveObj(int direction) override;
	int getType() override;
}

#endif