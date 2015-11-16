//#include "Player.h"
//#include "GameObject.h"
#include "GameUtils.h"
#include <glm/gtx/vector_angle.hpp>
#include "Game.h"

CPlayer::CPlayer()
{
	health = 100; // default health value
	velocity = 0.2f; // default velocity
	ammunition = 100; // default ammo amount
	
}


CPlayer::~CPlayer()
{
}


void CPlayer::OnKeyDown(const SDL_Keycode *Key)
{
	if (*Key == SDLK_UP){
		glm::vec3 move = GameObject::GetPos();
		move.y += velocity;
		GameObject::SetPos(move);
	}
	else
	if (*Key == SDLK_DOWN) {
		glm::vec3 move = GameObject::GetPos();	
		move.y -= velocity;
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

void CPlayer::Update(uint32 dt){
	sprite_anim->SetPos(this->GetPos());
}

void CPlayer::OnMouseMove(const MouseArgs *Args){	
	glm::vec2 mouse_vec, ref_vec(1.0f,0.0), obj_pos;
	CGame::GetGameIntance().GetMouse2dWorldPositon(mouse_vec.x, mouse_vec.y);

	obj_pos.x = this->GetPos().x;
	obj_pos.y = this->GetPos().y;

	mouse_vec = glm::normalize(mouse_vec - obj_pos);
	float angle = glm::orientedAngle(ref_vec, mouse_vec);
	sprite_anim->SetAngleZ(angle);
}