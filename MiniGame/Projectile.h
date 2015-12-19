#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GameObject.h"
#include "Animation.h"

class CProjectile : public GameObject
{
protected:
	uint32 damage;
	uint32 ID;
	glm::vec3 direction;
	float velocity;

	
	void Move(const uint32 dt);
	void OnCollision(GameObject* obj);

public:
	CSpriteAnimation *sprite_anim;
	void CalculateDirection();
	void Update(uint32 dt);
	
	CProjectile();
	CProjectile(const uint32 damage, const float velocity);
	~CProjectile();
};


#endif // CPROJECTILE_H