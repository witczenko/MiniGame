#ifndef _ASTEROID_H
#define _ASTEROID_H

#include "Game.h"
#include "GameUtils.h"
#include "GameObject.h"
#include "Sprite.h"

class CAsteroid :
	public GameObject
{
public:
	CAsteroid();
	~CAsteroid();

	CSprite *sprite;
private:
	int32 durability;
	float32 velocity;
	float32 angular_velocity;
	glm::vec3 direction;

protected:
	void Update(uint32 dt);
};

class CAsteroidManager{
public:
	CAsteroidManager();
	~CAsteroidManager();
	void Update(uint32 dt);
	void Init();
private:
	std::vector<CAsteroid*> AsteroidCollection;
	CGame & Game;
};

#endif 

