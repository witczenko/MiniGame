#ifndef _ASTEROID_H
#define _ASTEROID_H

#include "GameObject.h"
#include "Sprite.h"


class CAsteroid :
	public GameObject
{
public:
	CAsteroid();
	~CAsteroid();

private:
	int32 durability;
};

#endif 

