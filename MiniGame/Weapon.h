#ifndef WEAPON_H
#define WEAPON_H

#include "Types.h"
#include "Scene.h"

/// CONSTANTS ///

static const uint32 RAPID_GUN_HEAT_LIMIT = 3000;
static const uint32 BULLET_DAMAGE = 10;
static const float BULLET_VELOCITY = 10.f;

static const uint32 ROCKET_LAUNCHER_RELOAD_DELAY = 3000;
static const uint32 ROCKET_LAUNCHER_AMMUNITION = 10;
static const uint32 ROCKET_DAMAGE = 100;
static const float ROCKET_VELOCITY = 4.f;


/// RAPID GUN ///

class CRapidGun
{
public:
	bool overheated;
	uint32 heat_level;
	uint32 damage;

	CSpriteAnimation *sprite_anim;
	CScene &Scene;
	glm::vec3 pos;

	CRapidGun();
	CRapidGun(const uint32 damage);
	~CRapidGun();

	void CoolDown(const uint32);
	void CreateBullet();
	void Shoot(const uint32);
	void Update(const uint32 dt);
};

/// ROCKET LAUNCHER ///

class CRocketLauncher
{
public:
	bool ready;
	uint32 ammunition;
	uint32 reload_time;
	uint32 damage;

	CSpriteAnimation *sprite_anim;
	CScene &Scene;
	glm::vec3 pos;

	CRocketLauncher();
	CRocketLauncher(const uint32 damage);
	~CRocketLauncher();

	void Reload(const uint32 dt);
	void CreateRocket();
	void Shoot(const uint32);
	void Update(const uint32 dt);
};

#endif // WEAPON_H