#ifndef _GOLD_H_
#define _GOLD_H_

#include "item.h"

class Gold: public Item {
	std::string description;
	bool dragonHoard;
	bool slain = false; // whether or not Dragon is slain
	bool steal = false;
	NPC * npc;

public:
	// constructor and destructor
	Gold(int value, int x, int y, bool drgn);
	~Gold();

	// accessors and mutators
	std::string getDescript();
	bool getDrgn();
	bool getSlain();
	NPC *& getNPC();

	// other methods
	void useItem(PC &pc) override;

	void assignNPC(NPC &npc);
	bool allowPickup();
	bool allowSteal();
};

#endif
