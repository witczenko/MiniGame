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
	void SetCollideFlag(bool flag);	
	void SetCollisionRad(float rad);
	bool GetCollideFlag() const;
	float GetCollisionRad() const;
	void SetPos(glm::vec2 pos);
	uint32 GetID() const;
	OBJECT_TYPE GetType() const;

	virtual void Update(uint32 dt){};
	virtual void OnCollision(GameObject* obj){};

protected:
	OBJECT_TYPE type;
private:
	
	bool collide; 
	float collsion_rad;
	uint32 ID;
	glm::vec3 pos;
};

#endif

