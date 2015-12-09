#include "Mob.h"
#include "Game.h"
#include "GameUtils.h"

static const float MOB_VELOCITY = 1.5f;
static const uint8 MOB_HEALTH = 100;
static const uint8 MOB_DAMAGE = 10;

CMob::CMob():
sprite_anim(NULL)
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
	CMob();
	
	effect_type = type;
	this->type = OBJECT_TYPE::MOB;
}

void CMob::CleanUp()
{
	if (sprite_anim)
	{
		delete sprite_anim;
		sprite_anim = NULL;
	}
}

CMob::~CMob()
{
	CleanUp();
}


glm::vec3 CMob::getTarget()
{
	return target;
}

void CMob::setTarget(const glm::vec3 target)
{
	this->target = target;
}

void CMob::DirectionUpdate()
{
	if (glm::length(target - GetPos()) > 0.2)
		direction = glm::normalize(target - GetPos());
	else
		direction = glm::vec3(0.0f);
}

void CMob::RotateToTarget()
{
	
	glm::vec2 ref_vec(0.0f, 1.0f);
	glm::vec2 norm_direction(direction);
	norm_direction = glm::normalize(norm_direction);
	float angle = R2D(glm::orientedAngle(ref_vec, norm_direction));
	sprite_anim->SetAngleZ(angle);
}

void CMob::Move(uint32 dt)
{
	glm::vec3 pos_incr = direction*MOB_VELOCITY*(float)(dt / 1000.0f);
	SetPos(GetPos() + pos_incr);
	sprite_anim->SetPos(glm::vec2(GetPos()));
}

void CMob::Update(uint32 dt)
{
	DirectionUpdate();
	RotateToTarget();
	Move(dt);
}


void CMob::OnCollision(GameObject* obj){
	/*
	switch (obj->GetType())
	{
	case OBJECT_TYPE::PLAYER:
	{
		glm::vec3 obj_pos = obj->GetPos();
		obj_pos += (this->direction)*0.1f;
		obj->SetPos(obj_pos);
		break;
	}
	case OBJECT_TYPE::MOB:
	{
		break;
	}		
		
	}
	*/
}