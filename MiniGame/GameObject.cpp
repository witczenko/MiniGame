#include "GameObject.h"
#define START_POS (glm::vec3(0.0f, 0.0f, 0.0f))

static uint32 OBJECT_COUNTER;


GameObject::GameObject() :pos(START_POS)
{
	ID = OBJECT_COUNTER;
	OBJECT_COUNTER++;
}

GameObject::GameObject(glm::vec3 init_pos) :pos(init_pos)
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


