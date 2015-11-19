
#ifndef MOB_H
#define MOB_H

#include "Player.h"
#include "Types.h"
#include "GameObject.h"

class CMob
{
	uint16 health;
	EFFECT_TYPE type;
	uint16 damage;
	float32 velocity;


public:
	CMob(); // spawning
	~CMob();

	void move();
	void attack();
	void die();
};

#endif // MOB_H