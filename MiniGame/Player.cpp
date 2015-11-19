
#include "Player.h"
#include "GameObject.h"
#include "Types.h"


//#include "Player.h"
//#include "GameObject.h"
#include "GameUtils.h"
#include <glm/gtx/vector_angle.hpp>
#include "Game.h"

CPlayer::CPlayer()
{
	health = 100; // default health value
	velocity = 0.05f; // default velocity
	
	for (int i = UNDEFINED; i < EFFECT_COUNT; i++) // default status array values
	{
		status[i].type = static_cast<EFFECT_TYPE>(i);
		status[i].active = false;
		status[i].duration = 0;
	}
	sprite_anim = NULL;

	primary.heat_level = 0;
	primary.overheated = false;

	secondary.ammunition = AMMUNITION;
	secondary.ready = true;
	secondary.reload_time = 0;
}


CPlayer::~CPlayer()
{
}


void CPlayer::OnKeyDown(const SDL_Keycode *Key)
{
	if (*Key == SDLK_w){
		glm::vec3 move = GameObject::GetPos();
		move.y += velocity;
		GameObject::SetPos(move);
	}
	else
	if (*Key == SDLK_s) {
		glm::vec3 move = GameObject::GetPos();	
		move.y -= velocity;
		GameObject::SetPos(move);
	}
	else
	if (*Key == SDLK_a) {
		glm::vec3 move = GameObject::GetPos();
		move.x -= velocity;
		GameObject::SetPos(move);
	}
	else
	if (*Key == SDLK_d) {
		glm::vec3 move = GameObject::GetPos();
		move.x += velocity;
		GameObject::SetPos(move);
	}
}

void CPlayer::OnMouseMove(const MouseArgs *Args){
	glm::vec2 mouse_vec, ref_vec(1.0f, 0.0), obj_pos;
	CGame::GetGameIntance().GetMouse2dWorldPositon(mouse_vec.x, mouse_vec.y);

	obj_pos.x = this->GetPos().x;
	obj_pos.y = this->GetPos().y;

	mouse_vec = glm::normalize(mouse_vec - obj_pos);
	float angle = glm::orientedAngle(ref_vec, mouse_vec);
	sprite_anim->SetAngleZ(angle);
}

void CPlayer::WeaponStatusUpdate(uint32 dt)
{
	if (primary.heat_level == HEAT_LIMIT)
	{
		primary.overheated = true;
	}

	if (primary.heat_level > 0)
	{
		if (primary.heat_level < dt)
		{
			primary.heat_level = 0;
			primary.overheated = false;
		}
		else primary.heat_level -= dt;
	}


	if (!secondary.ready)
	{
		if (secondary.reload_time < dt)
		{
			secondary.reload_time = 0;
			secondary.ready = true;
		}
		else secondary.reload_time -= dt;
	}

	


}

void CPlayer::Update(uint32 dt){
	sprite_anim->SetPos(this->GetPos());
	WeaponStatusUpdate(dt);
}





void CPlayer::OnMouseButtonDown(const MouseArgs *Args)
{
	switch (Args->button)
	{
	case MLeft:
	{
				  if (!primary.overheated)
				  {
					  // shoot
					  // remember to call 
					  primary.heat_level++;
				  }
				  break;

	}
	case MRight:
	{
				   if (secondary.ready && (secondary.ammunition > 0))
				   {
					   //shoot
					   secondary.ammunition--;
					   secondary.ready = false;
					   secondary.reload_time = RELOAD_DELAY;
				   }
				   break;

	}
	}
}