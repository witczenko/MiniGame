#include "Mob.h"
#include "Mob.h"


CMob::CMob()
{
	id = MOB_NUMBER;
	MOB_NUMBER++;
	health = MOB_HEALTH;
	velocity = MOB_VELOCITY;
	damage = MOB_DAMAGE;
	type = EFFECT_TYPE::UNDEFINED;
}

CMob::CMob(const EFFECT_TYPE type)
{
	id = MOB_NUMBER;
	MOB_NUMBER++;
	health = MOB_HEALTH;
	velocity = MOB_VELOCITY;
	damage = MOB_DAMAGE;
	this->type = type;
}

CMob::~CMob()
{
}


glm::vec3 CMob::getTarget()
{
	return target;
}

void CMob::setTarget(const glm::vec3 target)
{
	this->target = target;
}

void CMob::VectorUpdate()
{
	if (glm::length(target - GetPos()) > 0.2)
		vector = glm::normalize(target - GetPos());
	else
		vector = glm::vec3(0.0f);
}

void CMob::move(uint32 dt)
{
	glm::vec3 pos_incr = vector*MOB_VELOCITY*(float)(dt / 1000.0f);
	SetPos(GetPos() + pos_incr);
	sprite_anim->SetPos(glm::vec2(this->GetPos()));
}

void CMob::Update(uint32 dt)
{
	VectorUpdate();
	move(dt);
}