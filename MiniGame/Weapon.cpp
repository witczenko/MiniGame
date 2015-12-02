#include "Weapon.h"

/// RAPID GUN ///

CRapidGun::CRapidGun()
{
	heat_level = 0;
	overheated = false;
	damage = RAPID_GUN_DAMAGE;
}

CRapidGun::CRapidGun(const uint32 damage)
{
	CRapidGun();
	this->damage = damage;
}

CRapidGun::~CRapidGun()
{

}

void CRapidGun::CoolDown(const uint32 dt)
{
	if (heat_level > 0)
	{
		if (heat_level <= dt)
		{
			heat_level = 0;
			overheated = false;
		}
		else heat_level -= dt;
	}

}

void CRapidGun::Shoot(const uint32 dt)
{
	if (!overheated)
	{
		// shoot
		heat_level += dt;
		if (heat_level >= RAPID_GUN_HEAT_LIMIT)
		{
			overheated = true;
		}
	}
};

void CRapidGun::Update(const uint32 dt)
{
	if (overheated) CoolDown(dt);
	else Shoot(dt);
}

/// ROCKET LAUNCHER ///

CRocketLauncher::CRocketLauncher()
{
	ready = true;
	reload_time = 0;
	ammunition = ROCKET_LAUNCHER_AMMUNITION;
	damage = ROCKET_LAUNCHER_DAMAGE;
}

CRocketLauncher::CRocketLauncher(const uint32 damage)
{
	CRocketLauncher();
	this->damage = damage;
}

CRocketLauncher::~CRocketLauncher()
{

}

void CRocketLauncher::Reload(const uint32 dt)
{
	if (reload_time < dt)
	{
		reload_time = 0;
		ready = true;
	}
	else reload_time -= dt;
}

void CRocketLauncher::Shoot()
{
	if (ready && (ammunition > 0))
	{
		//shoot
		ready = false;
		ammunition--;
		reload_time = ROCKET_LAUNCHER_RELOAD_DELAY;
	}
}


