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

class CPlayer : public GameObject //, public CSpriteAnimation ??? player animation ???
{
public:

	static const uint16 EFFECT_DURATION = 3000;
	static const uint16 HEAT_LIMIT = 3000;
	static const uint16 RELOAD_DELAY = 2000;
	static const uint8 AMMUNITION = 5;
	static const uint8 PRIM_DMG = 10;
	static const uint8 SEC_DMG = 30;

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

	uint16 health;
	float32 velocity;
	
	Prim_Weap primary;
	Sec_Weap secondary;

	CSpriteAnimation *sprite_anim;

	Effect status[EFFECT_COUNT];

	CPlayer();
	~CPlayer();

	void WeaponStatusUpdate(uint32 dt);

protected:
	void OnKeyDown(const SDL_Keycode *Key);
	void Update(uint32 dt);
	void OnMouseMove(const MouseArgs *Args);
	void OnMouseButtonDown(const MouseArgs *Args);
	//void OnMouseButtonUp(const MouseArgs *Args);
	//void OnMouseWheelBackward();
	//void OnMouseWheelForward();

};

#endif // PLAYER_H