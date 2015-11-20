#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Types.h"
#include <glm\glm.hpp>
#include "Input.h"



class GameObject : public CInputInterface
{
public:
	enum OBJECT_TYPE{
		UNDEFINED = 0,
		PLAYER,
		SPRITE,
		SPRITE_ANIM,
		TILE,
		MOB,
		TYPE_COUNT,
	};

	GameObject();
	GameObject(glm::vec3 init_pos);
	~GameObject();

	glm::vec3 GetPos() const;
	void SetPos(glm::vec3 pos);
	void SetPos(glm::vec2 pos);
	uint32 GetID() const;

	virtual void Update(uint32 dt){};

private:
	uint32 ID;
	glm::vec3 pos;
};

#endif

