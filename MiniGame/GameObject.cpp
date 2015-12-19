#include "GameObject.h"
#include "Game.h"

#define START_POS (glm::vec3(0.0f, 0.0f, 0.0f))
#define COLLISON_RAD (0.25f)

static uint32 OBJECT_COUNTER;

GameObject::GameObject() :
pos(START_POS),
collsion_rad(COLLISON_RAD),
collide(false),
type(OBJECT_TYPE::UNDEFINED),
Game(CGame::GetGameInstance()),
status(OBJECT_STATUS::ALIVE)
{
	ID = OBJECT_COUNTER;
	OBJECT_COUNTER++;
}

GameObject::GameObject(glm::vec3 init_pos):
pos(init_pos),
collsion_rad(COLLISON_RAD),
collide(false),
type(OBJECT_TYPE::UNDEFINED),
Game(CGame::GetGameInstance()),
status(OBJECT_STATUS::ALIVE)
{
	ID = OBJECT_COUNTER;
	OBJECT_COUNTER++;
}


GameObject::~GameObject()
{
}

uint32 GameObject::GetID() const{
	return ID;
}

glm::vec3 GameObject::GetPos() const{
	return pos;
}

void GameObject::SetPos(glm::vec3 pos){
	this->pos = pos;
}

void GameObject::SetCollideFlag(bool flag){
	this->collide = flag;
}

bool GameObject::GetCollideFlag() const{
	return this->collide;
}

void GameObject::SetCollisionRad(float rad){
	this->collsion_rad = rad;
}

float GameObject::GetCollisionRad() const{
	return this->collsion_rad;
}

void GameObject::SetPos(glm::vec2 pos){
	this->pos.x = pos.x;
	this->pos.y = pos.y;
}

GameObject::OBJECT_TYPE GameObject::GetType() const{
	return this->type;
}

uint32 GameObject::GetObjectCount(){
	return OBJECT_COUNTER;
}
