
#include "Mob.h"
#include <glm/gtx/vector_angle.hpp>


CMob::CMob()
{
	id = MOB_NUMBER;
	MOB_NUMBER++;
	health = MOB_HEALTH;
	velocity = MOB_VELOCITY;
	damage = MOB_DAMAGE;
	effect_type = EFFECT_TYPE::UNDEFINED;
	type = OBJECT_TYPE::MOB;

	target = glm::vec3(0.0f,0.0f,0.0f);
	direction = glm::vec3(0.0f, 0.0f, 0.0f);
}

CMob::CMob(const EFFECT_TYPE type)
{
	id = MOB_NUMBER;
	MOB_NUMBER++;
	health = MOB_HEALTH;
	velocity = MOB_VELOCITY;
	damage = MOB_DAMAGE;
	
	effect_type = type;
	this->type = OBJECT_TYPE::MOB;

	direction = glm::vec3(0.0f, 0.0f, 0.0f);
	target = glm::vec3(0.0f, 0.0f, 0.0f);
}

void CMob::CleanUP()
{
	if (sprite_anim)
	{
		delete sprite_anim;
		sprite_anim = NULL;
	}
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
		direction = glm::normalize(target - GetPos());
	else
		direction = glm::vec3(0.0f);
}

void CMob::RotateToTarget()
{
	VectorUpdate();
	glm::vec2 ref_vec(-1.0f, 0.0f);
	glm::vec2 norm_direction(direction);
	norm_direction = glm::normalize(norm_direction);
	float angle = glm::orientedAngle(ref_vec, norm_direction);
	sprite_anim->SetAngleZ(angle);
}

void CMob::move(uint32 dt)
{
	glm::vec3 pos_incr = direction*MOB_VELOCITY*(float)(dt / 1000.0f);
	SetPos(GetPos() + pos_incr);
	sprite_anim->SetPos(glm::vec2(GetPos()));
}

void CMob::Update(uint32 dt)
{
	printf("\nAngle: %f",sprite_anim->GetAngleZ());
	RotateToTarget();
	move(dt);
}

void CMob::OnCollision(GameObject* obj){
	if (obj->GetType() == OBJECT_TYPE::PLAYER){
		glm::vec3 pos = obj->GetPos();
		pos.y -= 0.25;
		obj->SetPos(pos);
	}

}