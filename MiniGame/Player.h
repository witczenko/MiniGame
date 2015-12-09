#ifndef PLAYER_H
#define PLAYER_H

#include "Types.h"
#include "GameObject.h"
#include "Animation.h"
#include "Weapon.h"

enum EFFECT_TYPE{
	UNDEFINED = 0,
	SLOW,
	FREEZE,
	INVERT,
	LOCK,
	//SPEED,
	//SHIELD,

	EFFECT_COUNT,

};

enum STATE_TYPE{
	UP = 1,
	DOWN = 1<<1,
	RIGHT = 1<<2,
	LEFT = 1<<3,
	LMB = 1<<4,
	RMB = 1<<5
};


class CPlayer : public GameObject
{
public:

	struct Effect{
		EFFECT_TYPE type;
		bool active;
		uint16 duration;
	};
	//CScene &Scene;

	uint8 health;
	float32 velocity;
	
	CRapidGun primary;
	CRocketLauncher secondary;

	CSpriteAnimation *sprite_anim;

	Effect status[EFFECT_COUNT];

	CPlayer();
	~CPlayer();

private:
	void WeaponStatusUpdate(uint32 dt);
	void RotateToMouse();
	void Move(uint32 dt);

	uint32 InputState;
	glm::vec3 old_pos;
protected:
	void OnKeyDown(const SDL_Keycode *Key);
	void Update(uint32 dt);
	void OnMouseMove(const MouseArgs *Args);
	void OnMouseButtonDown(const MouseArgs *Args);
	void OnKeyUp(const SDL_Keycode *Key);
	void OnMouseButtonUp(const MouseArgs *Args);
	void OnCollision(GameObject* obj);
	//void OnMouseWheelForward();
};

#endif // PLAYER_H