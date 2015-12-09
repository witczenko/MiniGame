#include "Weapon.h"
#include "Projectile.h"
#include "Scene.h"
#include "Game.h"

/// RAPID GUN ///

CRapidGun::CRapidGun():
sprite_anim(NULL),
Scene(CGame::GetGameInstance().GetScene())
{
	heat_level = 0;
	overheated = false;
	damage = BULLET_DAMAGE;
	
}

CRapidGun::CRapidGun(const uint32 damage):
Scene(CGame::GetGameInstance().GetScene())
{
	CRapidGun();
	this->damage = damage;
}

CRapidGun::~CRapidGun()
{
	if (this->sprite_anim)
	{
		delete this->sprite_anim;
		this->sprite_anim = NULL;
	}
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

void CRapidGun::CreateBullet()
{
	CProjectile *Bullet = new CProjectile(BULLET_DAMAGE, BULLET_VELOCITY);

	if (Bullet)
	{
		Bullet->SetPos(this->pos);
		Bullet->SetCollideFlag(true);

		Bullet->sprite_anim = this->sprite_anim;


		if (Bullet->sprite_anim)
		Scene.AddObject(Bullet, GameObject::OBJECT_TYPE::PROJECTILE);
		else delete Bullet;
	}
	Bullet = NULL;
	
}


void CRapidGun::Shoot(const uint32 dt)
{
	if (!overheated)
	{
		CreateBullet();

		heat_level += dt;
		if (heat_level >= RAPID_GUN_HEAT_LIMIT)
		{
			overheated = true;
		}
	}
};

void CRapidGun::Update(const uint32 dt)
{
}

/// ROCKET LAUNCHER ///

CRocketLauncher::CRocketLauncher():
sprite_anim(NULL),
Scene(CGame::GetGameInstance().GetScene())
{
	ready = true;
	reload_time = 0;
	ammunition = ROCKET_LAUNCHER_AMMUNITION;
	damage = ROCKET_DAMAGE;
}

CRocketLauncher::CRocketLauncher(const uint32 damage):
Scene(CGame::GetGameInstance().GetScene())
{
	CRocketLauncher();
	this->damage = damage;
}

CRocketLauncher::~CRocketLauncher()
{
	if (this->sprite_anim)
	{
		delete this->sprite_anim;
		this->sprite_anim = NULL;
	}
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

void CRocketLauncher::CreateRocket()
{

	CProjectile *Rocket = new CProjectile(ROCKET_DAMAGE, ROCKET_VELOCITY);

	if (Rocket)
	{
		Rocket->SetPos(this->pos);
		Rocket->SetCollideFlag(true);

		Rocket->sprite_anim = this->sprite_anim;

		if (Rocket->sprite_anim)
			Scene.AddObject(Rocket, GameObject::OBJECT_TYPE::PROJECTILE);
		else delete Rocket;
	}
	Rocket = NULL;
}

void CRocketLauncher::Shoot(uint32 dt)
{
	if (ready && (ammunition > 0))
	{
		CreateRocket();
		ready = false;
		ammunition--;
		reload_time = ROCKET_LAUNCHER_RELOAD_DELAY;
	}
}


