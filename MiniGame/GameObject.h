#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Types.h"
#include <glm\glm.hpp>

class GameObject
{
public:
	GameObject();
	GameObject(glm::vec3 init_pos);
	~GameObject();

	glm::vec3 GetPos() const;
	uint32 GetID() const;

private:
	uint32 ID;
	glm::vec3 pos;
};

#endif

