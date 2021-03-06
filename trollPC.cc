#include "trollPC.h"
#include "character.h"
#include "object.h"
#include "pc.h"
#include "npc.h"
#include "factory.h"

void TrollPC::attack(NPC& enemy){
	int hit = 1;
	if (enemy.getType() == "halflingNPC") {
		Factory f;
		hit = f.randInt(1);
	}
	if (hit) {
		int damage = calcDmg(this->getAtk(), enemy.getDef());
		enemy.changeHP(-damage, false);
	}
}

void TrollPC::defendFrom(NPC& enemy){
	int damage = calcDmg(enemy.getAtk(), this->getDef());
	this->changeHP(-damage, false);

	string temp = enemy.getType();
	string attacker = temp.substr(0, temp.length() - 3);
	this->notifyDisplay(attacker + " attacks PC!");
}

void TrollPC::nextTurn(){
	this->notifyNPCs();
	this->notifyDisplay();
	this->changeHP(5, false);
}

TrollPC::TrollPC(int x, int y, Tile *t) {
	this->setStats(120, 25, 15);
	this->setMaxHP(120);
	this->setType("TrollPC");
	this->setCoords(x,y);
	this->setTile(t);
}

TrollPC::~TrollPC() {}
