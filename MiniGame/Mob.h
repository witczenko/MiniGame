
#ifndef MOB_H
#define MOB_H

#include "Player.h"
#include "Types.h"
#include "GameObject.h"
#include "Animation.h"

static uint32 MOB_NUMBER = 0;

static const float MOB_VELOCITY = 1.5f;
static const uint8 MOB_HEALTH = 100;
static const uint8 MOB_DAMAGE = 10;


class CMob: public GameObject
{
	uint32 id;
	uint16 health;
	EFFECT_TYPE type;
	uint16 damage;
	float32 velocity;
	glm::vec3 target;
	glm::vec3 direction;

	void VectorUpdate();
	void RotateToTarget();
	void move(uint32 dt);
	void attack();
	void die();

public:
	CSpriteAnimation *sprite_anim;


	CMob(); // spawning
	CMob(const EFFECT_TYPE type);
	~CMob();

	
	void Update(uint32 dt);
	void CleanUP();
	

	glm::vec3 getTarget();
	void setTarget( const glm::vec3 target );
	
};

#endif // MOB_H