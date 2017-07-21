#include "boostdef.h"

using namespace std;

// constructor and destructor
BoostDef::RestoreHealth(BasicPotion *base) :
	PotionDecorator{base}, defense{5} {
		lifetime = false;
	}

BoostDef::~RestoreHealth() {}

// accessors and mutators
bool BoostDef::getLifetime() {
	return lifetime;
} 

void BoostDef::resetEffect(PC &pc) {
	pc->changeDef(-defense);
}

int BoostDef::getDefense() {
	return defense;
}


// other methods
void BoostDef::useItem(PC &pc) {
	pc->changeDef(defense);
}