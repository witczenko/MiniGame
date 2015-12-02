#include "Projectile.h"
#include "Game.h"
#include "Weapon.h"

/// CONSTANTS & STATICS ///

static uint32 PROJECTILE_AMOUNT = 0;
static const uint32 PROJECTILE_DAMAGE = 10;
static const float PROJECTILE_VELOCITY = 100;

/// PROJECTILE ///

void CProjectile::CalculateDirection()
{
	glm::vec2 mouse_vec, ref_vec(0.0f, 1.0f), obj_pos;
	CGame::GetGameIntance().GetMouse2dWorldPositon(mouse_vec.x, mouse_vec.y);
	(glm::vec2)direction = glm::normalize(mouse_vec - (glm::vec2)GetPos());
}

CProjectile::CProjectile()
{
	type = OBJECT_TYPE::PROJECTILE;
	ID = PROJECTILE_AMOUNT;
	PROJECTILE_AMOUNT++;
	damage = PROJECTILE_DAMAGE;
	velocity = PROJECTILE_VELOCITY;

	CalculateDirection();
}

CProjectile::CProjectile(const uint32 damage, const float velocity)
{
	CProjectile();
	this->damage = damage;
	this->velocity = velocity;

}

CProjectile::~CProjectile()
{

}

void CProjectile::Move(const uint32 dt)
{
}

void CProjectile::OnCollision()
{

}
