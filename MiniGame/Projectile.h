#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GameObject.h"

class CProjectile : public GameObject
{
protected:
	uint32 damage;
	uint32 ID;
	glm::vec3 direction;
	float velocity;

	void CalculateDirection();
	void Move(const uint32 dt);
public:
	//void Update(uint32 dt);
	void OnCollision();

	CProjectile();
	CProjectile(const uint32 damage, const float velocity);
	~CProjectile();
};


#endif // CPROJECTILE_H