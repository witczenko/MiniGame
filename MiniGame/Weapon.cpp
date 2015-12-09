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

void CRapidGun::CreateBullet(const float angle)
{
	CProjectile *Bullet = new CProjectile(BULLET_DAMAGE, BULLET_VELOCITY);

	if (Bullet)
	{
		Bullet->SetPos(this->pos);
		Bullet->SetCollideFlag(true);
		Bullet->CalculateDirection();
		Bullet->sprite_anim = new CSpriteAnimation();
		Bullet->sprite_anim->SetAnimation(this->sprite_anim->GetAnimation());
		Bullet->sprite_anim->SetFPS(24);
		Bullet->sprite_anim->SetHeight(0.1f);
		Bullet->sprite_anim->SetWidth(0.1f);
		Bullet->sprite_anim->SetPos(this->pos);
		Bullet->sprite_anim->SetAngleZ(angle);

		if (Bullet->sprite_anim)
		Scene.AddObject(Bullet, GameObject::OBJECT_TYPE::PROJECTILE);
		else delete Bullet;
	}
	Bullet = NULL;
	
}


void CRapidGun::Shoot(const uint32 dt, const float angle)
{
	static uint32 shoot_pause = 0;

	if (!overheated)
	{
		if (shoot_pause > 50){
			CreateBullet(angle);
			shoot_pause = 0;
		}
		shoot_pause += dt;

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

void CRocketLauncher::CreateRocket(const float angle)
{

	CProjectile *Rocket = new CProjectile(ROCKET_DAMAGE, ROCKET_VELOCITY);

	if (Rocket)
	{
		Rocket->SetPos(this->pos);
		Rocket->SetCollideFlag(true);
		Rocket->CalculateDirection();
		Rocket->sprite_anim = new CSpriteAnimation();
		Rocket->sprite_anim->SetAnimation(this->sprite_anim->GetAnimation());
		Rocket->sprite_anim->SetFPS(24);
		Rocket->sprite_anim->SetHeight(0.2f);
		Rocket->sprite_anim->SetWidth(0.2f);
		Rocket->sprite_anim->SetPos(this->pos);
		Rocket->sprite_anim->SetAngleZ(angle);

		if (Rocket->sprite_anim)
			Scene.AddObject(Rocket, GameObject::OBJECT_TYPE::PROJECTILE);
		else delete Rocket;
	}
	Rocket = NULL;
}

void CRocketLauncher::Shoot(const uint32 dt, const float angle)
{
	if (ready && (ammunition > 0))
	{
		CreateRocket(angle);
		ready = false;
		ammunition--;
		reload_time = ROCKET_LAUNCHER_RELOAD_DELAY;
	}
}


