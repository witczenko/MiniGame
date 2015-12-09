#ifndef MOB_H
#define MOB_H

#include "Player.h"
#include "GameObject.h"
#include "Animation.h"

static uint32 MOB_NUMBER = 0;

class CMob: public GameObject
{
	uint32 id;
	uint16 health;
	EFFECT_TYPE effect_type;
	uint16 damage;
	float32 velocity;
	glm::vec3 target;
	glm::vec3 direction;

	void DirectionUpdate();
	void RotateToTarget();
	void Move(uint32 dt);
	//void attack();
	//void die();

protected:
	void OnCollision(GameObject* obj);

public:
	CSpriteAnimation *sprite_anim;


	CMob(); // spawning
	CMob(const EFFECT_TYPE type);
	~CMob();

	
	void Update(uint32 dt);
	void CleanUp();
	

	glm::vec3 getTarget();
	void setTarget( const glm::vec3 target );
	
};

#endif // MOB_H