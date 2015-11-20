#ifndef PLAYER_H
#define PLAYER_H

#include "Types.h"
#include "GameObject.h"
#include "Animation.h"

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

static const float32 PLAYER_VELOCITY = 2.5f;
static const uint16 PLAYER_EFFECT_DURATION = 3000;
static const uint16 PLAYER_HEAT_LIMIT = 3000;
static const uint16 PLAYER_RELOAD_DELAY = 2000;
static const uint8 PLAYER_AMMUNITION = 5;
static const uint8 PLAYER_PRIM_DMG = 1;
static const uint8 PLAYER_SEC_DMG = 50;
static const uint8 PLAYER_HEALTH = 100;


class CPlayer : public GameObject //, public CSpriteAnimation ??? player animation ???
{
public:

	struct Effect{
		EFFECT_TYPE type;
		bool active;
		uint16 duration;
	};

	struct Prim_Weap{
		bool overheated;
		uint16 heat_level;
	};

	struct Sec_Weap{
		bool ready;
		uint16 ammunition;
		uint16 reload_time;
	};

	uint8 health;
	float32 velocity;
	
	Prim_Weap primary;
	Sec_Weap secondary;

	CSpriteAnimation *sprite_anim;

	Effect status[EFFECT_COUNT];

	CPlayer();
	~CPlayer();
private:
	void WeaponStatusUpdate(uint32 dt);
	void RotateToMouse();
	void move(uint32 dt);

	uint32 InputState;
protected:
	void OnKeyDown(const SDL_Keycode *Key);
	void Update(uint32 dt);
	void OnMouseMove(const MouseArgs *Args);
	void OnMouseButtonDown(const MouseArgs *Args);
	void OnKeyUp(const SDL_Keycode *Key);
	void OnMouseButtonUp(const MouseArgs *Args);
	//void OnMouseWheelBackward();
	//void OnMouseWheelForward();
};

#endif // PLAYER_H