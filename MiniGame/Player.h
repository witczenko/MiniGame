#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Types.h"
#include "GameObject.h"
//#include "Animation.h"



class CPlayer : public GameObject //, public CSpriteAnimation ??? player animation ???
{
	enum EFFECT_TYPE{
		UNDEFINED = 0,
		SLOW,
		FREEZE,
		INVERT,
		LOCK,
		SPEED,
		SHIELD,

		EFFECT_COUNT,

	};

	static const uint16 EFFECT_DURATION = 3000;

	struct Effect{
		EFFECT_TYPE type;
		bool active;
		uint32 duration;
	};

	uint16 health;
	float32 velocity;
	// face angle variable ??
	uint16 ammunition;
	Effect status[EFFECT_COUNT];
	

public:
	CPlayer();
	~CPlayer();

protected:
	void OnKeyDown(const SDL_Keycode *Key);
	void OnMouseMove(const MouseArgs *Args);
	void OnMouseButtonDown(const MouseArgs *Args);
	void OnMouseButtonUp(const MouseArgs *Args);
	void OnMouseWheelBackward();
	void OnMouseWheelForward();

};

#endif // PLAYER_H