
#include "Player.h"
#include "GameObject.h"
#include "Types.h"


//#include "Player.h"
//#include "GameObject.h"
#include "GameUtils.h"
#include <glm/gtx/vector_angle.hpp>
#include "Game.h"

CPlayer::CPlayer():
InputState(0)
{
<<<<<<< HEAD
	type = OBJECT_TYPE::PLAYER;

	health = HEALTH; // default health value
	velocity = 3.0f; // default velocity
=======
	health = PLAYER_HEALTH; // default health value
	velocity = PLAYER_VELOCITY; // default velocity
>>>>>>> origin/master
	
	for (int i = UNDEFINED; i < EFFECT_COUNT; i++) // default status array values
	{
		status[i].type = static_cast<EFFECT_TYPE>(i);
		status[i].active = false;
		status[i].duration = 0;
	}
	sprite_anim = NULL;

	primary.heat_level = 0;
	primary.overheated = false;

	secondary.ammunition = PLAYER_AMMUNITION;
	secondary.ready = true;
	secondary.reload_time = 0;
}


CPlayer::~CPlayer()
{
	if (sprite_anim){
		delete sprite_anim;
		sprite_anim = NULL;
	}
}


void CPlayer::OnKeyDown(const SDL_Keycode *Key)
{

	if (*Key == SDLK_w){
		InputState |= STATE_TYPE::UP;
	}
	else
	if (*Key == SDLK_s) {	
		InputState |= STATE_TYPE::DOWN;
	}
	else
	if (*Key == SDLK_a) {	
		InputState |= STATE_TYPE::LEFT;
	}
	else
	if (*Key == SDLK_d) {	
		InputState |= STATE_TYPE::RIGHT;
	}
}

void CPlayer::OnKeyUp(const SDL_Keycode *Key){
	if (*Key == SDLK_w){
		InputState &= ~STATE_TYPE::UP;
	}
	if (*Key == SDLK_s){
		InputState &= ~STATE_TYPE::DOWN;
	}
	if (*Key == SDLK_a){
		InputState &= ~STATE_TYPE::LEFT;
	}
	if (*Key == SDLK_d){
		InputState &= ~STATE_TYPE::RIGHT;
	}

}

void CPlayer::RotateToMouse(){
	glm::vec2 mouse_vec, ref_vec (0.0f, 1.0f), obj_pos;
	CGame::GetGameIntance().GetMouse2dWorldPositon(mouse_vec.x, mouse_vec.y);
	obj_pos.x = this->GetPos().x;
	obj_pos.y = this->GetPos().y;
	mouse_vec = glm::normalize(mouse_vec - obj_pos);
	float angle = glm::orientedAngle(ref_vec, mouse_vec);
	sprite_anim->SetAngleZ(angle);
}

void CPlayer::OnMouseMove(const MouseArgs *Args){
}

void CPlayer::WeaponStatusUpdate(uint32 dt)
{
	//system("cls");
	//std::cout << "\nHeat: " << primary.heat_level;
	//std::cout << "\nAmmo: " << secondary.ammunition;
	
	if (!(InputState & STATE_TYPE::LMB) || primary.overheated)
	{
		if (primary.heat_level > 0)
		{
			if (primary.heat_level < dt)
			{
				primary.heat_level = 0;
				primary.overheated = false;
			}
			else primary.heat_level -= dt;
		}
	}

	if (InputState & STATE_TYPE::LMB)
	{
		if (!primary.overheated)
		{
			// shoot
			primary.heat_level += dt;
			if (primary.heat_level >= PLAYER_HEAT_LIMIT)
			{
				primary.overheated = true;
			}
		}
	}
	
	if (InputState & STATE_TYPE::RMB)
	{
		if (secondary.ready && (secondary.ammunition > 0))
		{
			//shoot
			secondary.ready = false;
			secondary.ammunition--;
			secondary.reload_time = PLAYER_RELOAD_DELAY;
		}
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

void CPlayer::move(uint32 dt)
{
	float time = dt / 1000.f;
	glm::vec3 pos = GameObject::GetPos();

	sprite_anim->SetPos(this->GetPos());

	WeaponStatusUpdate(dt);

	if (InputState & STATE_TYPE::UP){
		pos.y += velocity*time;
	}

	if (InputState & STATE_TYPE::DOWN)
		pos.y -= velocity*time;

	if (InputState & STATE_TYPE::LEFT)
		pos.x -= velocity*time;

	if (InputState & STATE_TYPE::RIGHT){
		pos.x += velocity*time;
	}

	GameObject::SetPos(pos);
}

void CPlayer::Update(uint32 dt){
	RotateToMouse();
	move(dt);
}

void CPlayer::OnMouseButtonDown(const MouseArgs *Args)
{
	switch (Args->button)
	{
	case MLeft:
	{
		InputState |= STATE_TYPE::LMB;
		break;

	}
	case MRight:
	{
		InputState |= STATE_TYPE::RMB;
		break;

	}
	}
}

void CPlayer::OnMouseButtonUp(const MouseArgs *Args)
{
	switch (Args->button)
	{
	case MLeft:
	{
		InputState &= ~STATE_TYPE::LMB;
		break;

	}
	case MRight:
	{
		InputState &= ~STATE_TYPE::RMB;
		break;

	}
	}
}

void CPlayer::OnCollison(GameObject* obj){
	if (obj->GetType() == OBJECT_TYPE::SPRITE_ANIM)
		std::cout << "Collide with sprite animation\n";

	glm::vec3 pos = obj->GetPos();

	if (pos.x > this->GetPos().x)
		pos.x += 0.25;
	else
		pos.x -= 0.25;

	obj->SetPos(pos);
}