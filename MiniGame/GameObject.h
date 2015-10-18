#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Types.h"
#include <glm\glm.hpp>
#include "Input.h"



class GameObject : public CInputManager
{
public:
	enum OBJECT_TYPE{
		UNDEFINED = 0,
		PLAYER,
		SPRITE,
		SPRITE_ANIM,
		TILE,
		TYPE_COUNT,
	};

	GameObject();
	GameObject(glm::vec3 init_pos);
	~GameObject();

	glm::vec3 GetPos() const;
	void SetPos(glm::vec3 pos);
	uint32 GetID() const;

private:
	uint32 ID;
	glm::vec3 pos;
};

#endif

