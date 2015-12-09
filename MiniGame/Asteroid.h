#ifndef _ASTEROID_H
#define _ASTEROID_H

#include "Game.h"


class CAsteroid :
	public GameObject
{
public:
	CAsteroid();
	~CAsteroid();

	CSprite *sprite;
private:
	int32 durability;
	float velocity;
	CGame & Game;
	glm::vec2 driection;

protected:
	void Update(uint32 dt);
};



#endif 

