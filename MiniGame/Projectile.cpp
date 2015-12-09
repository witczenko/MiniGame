#include "Projectile.h"
#include "Game.h"
//#include "Weapon.h"

/// CONSTANTS & STATICS ///

static uint32 PROJECTILE_AMOUNT = 0;
static const uint32 PROJECTILE_DAMAGE = 10;
static const float PROJECTILE_VELOCITY = 100;

/// PROJECTILE ///

CProjectile::CProjectile():
sprite_anim(NULL)
{
	type = OBJECT_TYPE::PROJECTILE;
	ID = PROJECTILE_AMOUNT;
	PROJECTILE_AMOUNT++;
	damage = PROJECTILE_DAMAGE;
	velocity = PROJECTILE_VELOCITY;
}

CProjectile::CProjectile(const uint32 damage, const float velocity):
sprite_anim(NULL)
{
	CProjectile();
	this->damage = damage;
	this->velocity = velocity;

}

CProjectile::~CProjectile()
{
	if (this->sprite_anim)
	{
		delete this->sprite_anim;
		this->sprite_anim = NULL;
	}
}

void CProjectile::CalculateDirection()
{
	glm::vec3 mouse_vec;
	CGame::GetGameInstance().GetMouse2dWorldPositon(mouse_vec.x, mouse_vec.y);
	this->direction = glm::normalize(mouse_vec - this->GetPos());
}

void CProjectile::Move(const uint32 dt)
{
	glm::vec3 pos_incr = this->direction*this->velocity*(float)(dt / 1000.0f);
	this->SetPos(this->GetPos() + pos_incr);
	this->sprite_anim->SetPos(this->GetPos());
}

void CProjectile::OnCollision()
{

}

void CProjectile::Update(uint32 dt)
{
	Move(dt);
}
