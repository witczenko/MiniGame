#include "Player.h"
#include "GameUtils.h"
#include "Game.h"

static const float32 PLAYER_VELOCITY = 2.5f;
static const uint16 PLAYER_EFFECT_DURATION = 3000;
static const uint8 PLAYER_HEALTH = 100;

CPlayer::CPlayer():
InputState(0),
sprite_anim(NULL)
{
	type = OBJECT_TYPE::PLAYER;
	health = PLAYER_HEALTH; // default health value
	velocity = PLAYER_VELOCITY; // default velocity
	
	for (int i = UNDEFINED; i < EFFECT_COUNT; i++) // default status array values
	{
		status[i].type = static_cast<EFFECT_TYPE>(i);
		status[i].active = false;
		status[i].duration = 0;
	}
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
	CGame::GetGameInstance().GetMouse2dWorldPositon(mouse_vec.x, mouse_vec.y);
	obj_pos.x = this->GetPos().x;
	obj_pos.y = this->GetPos().y;
	mouse_vec = glm::normalize(mouse_vec - obj_pos);
	float angle = R2D(glm::orientedAngle(ref_vec, mouse_vec));
	sprite_anim->SetAngleZ(angle);
}

void CPlayer::OnMouseMove(const MouseArgs *Args){
}

void CPlayer::WeaponStatusUpdate(uint32 dt)
{
	primary.pos = this->GetPos();
	secondary.pos = this->GetPos();

	if (!(InputState & STATE_TYPE::LMB) || primary.overheated)
	{
		primary.CoolDown(dt);
	}

	if (InputState & STATE_TYPE::LMB)
	{
		primary.Shoot(dt,this->sprite_anim->GetAngleZ());
	}
	
	if (InputState & STATE_TYPE::RMB)
	{
		secondary.Shoot(dt,this->sprite_anim->GetAngleZ());
	}

	if (!secondary.ready)
	{
		secondary.Reload(dt);
	}
}

void CPlayer::Move(uint32 dt)
{
	float time = dt / 1000.f;
	glm::vec3 pos = GameObject::GetPos();

	sprite_anim->SetPos(this->GetPos());


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

	old_pos = GameObject::GetPos();
	GameObject::SetPos(pos);

	RotateToMouse();
}

void CPlayer::Update(uint32 dt){
	RotateToMouse();
	WeaponStatusUpdate(dt);
	Move(dt);
	char pos_str[64];
	sprintf(pos_str, "Player position (x,y,z) = (%f,%f,%f)\n", pos.x, pos.y, pos.z);

	Game.GetRenderLog() += pos_str;
	
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

void CPlayer::OnCollision(GameObject* obj){
	if (obj->GetType() == OBJECT_TYPE::TILE){
		this->SetPos(old_pos);
	}	
}