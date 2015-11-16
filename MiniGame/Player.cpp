#include "Player.h"
#include "GameObject.h"
#include "Types.h"


CPlayer::CPlayer()
{
	health = 100; // default health value
	velocity = 0.2f; // default velocity
	ammunition = 100; // default ammo amount

	for (int i = UNDEFINED; i < EFFECT_COUNT; i++) // default status array values
	{
		status[i].type = static_cast<EFFECT_TYPE>(i);
		status[i].active = false;
		status[i].duration = 0;
	}
	
}


CPlayer::~CPlayer()
{
}


void CPlayer::OnKeyDown(const SDL_Keycode *Key)
{
	if (*Key == SDLK_UP){
		glm::vec3 move = GameObject::GetPos();
		move.y -= velocity;
		GameObject::SetPos(move);
	}
	else
	if (*Key == SDLK_DOWN) {
		glm::vec3 move = GameObject::GetPos();
		move.y += velocity;
		GameObject::SetPos(move);
	}
	else
	if (*Key == SDLK_LEFT) {
		glm::vec3 move = GameObject::GetPos();
		move.x -= velocity;
		GameObject::SetPos(move);
	}
	else
	if (*Key == SDLK_RIGHT) {
		glm::vec3 move = GameObject::GetPos();
		move.x += velocity;
		GameObject::SetPos(move);
	}
}