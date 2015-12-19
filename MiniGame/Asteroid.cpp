#include "Asteroid.h"

static const int32 ASTER_BASE_DURABILITY = 100;
static const float32 ASTER_BASE_VELOCITY = 0.08f;
static const float32 ASTER_BASE_ANGULAR_VELOCITY = 250.0f;
static const int32 ASTER_MANAGER_ASTER_COUNT = 50;
static const glm::vec3 ASTER_BASE_DIR(0.0f, -1.0f, 0.0f);

/* ASTEROID */
CAsteroid::CAsteroid():
sprite(NULL)
{
	this->type = OBJECT_TYPE::ASTEROID;

	float rand_float1 = (rand() / (float)RAND_MAX);
	
	this->durability = ASTER_BASE_DURABILITY + (rand() % 50);
	this->velocity = ASTER_BASE_VELOCITY + rand_float1;
	this->angular_velocity = ASTER_BASE_ANGULAR_VELOCITY + ((rand() % 150));
	this->direction = ASTER_BASE_DIR;
	
	int tex = rand() % 3;
	uint32 texId;
	if (tex == 1)
		texId = Game.GetTextureManager().GetTexture("gfx/Spaceship_art_pack/Aestroids/aestroid_dark.png");
	else
		texId = Game.GetTextureManager().GetTexture("gfx/Spaceship_art_pack/Aestroids/aestroid_brown.png");

	sprite = new CSprite(glm::vec3(0.0f, 10.0f, 0.01f), 1.5f, 1.5f, texId);
	float aster_size = (rand_float1)/3.5f;
	if (aster_size < 0.1) aster_size = 0.1f;
	sprite->SetWidth(aster_size);
	sprite->SetHeight(aster_size);
}


CAsteroid::~CAsteroid()
{
	if (sprite){
		delete sprite;
		sprite = NULL;
	}
}

void CAsteroid::Update(uint32 dt){
	float t = dt / 1000.0f;
	glm::vec3 new_pos = this->GetPos() + velocity*direction*t;
	this->SetPos(new_pos);
	sprite->SetPos(new_pos);
	sprite->SetAngleZ(sprite->GetAngleZ() + angular_velocity*t);

	if (pos.y < -10) pos.y = 10.f;
}

void CAsteroid::OnCollision(GameObject* obj){
	if (obj->GetType() == OBJECT_TYPE::PROJECTILE)
		status = OBJECT_STATUS::DEAD;
}


/* ---- ASTEROID MANAGER ---- */
CAsteroidManager::CAsteroidManager() :
Game(CGame::GetGameInstance())
{
}


CAsteroidManager::~CAsteroidManager()
{
	AsteroidCollection.clear();
}

void CAsteroidManager::Update(uint32 dt){
	float t = dt / 1000.0f;

}

void CAsteroidManager::Init(){
	glm::vec3 start_pos(-5.0f, 20.0f, 0.01f);

	for (int32 i = 0; i < ASTER_MANAGER_ASTER_COUNT; i++){
		CAsteroid* aster = new CAsteroid();
		aster->SetPos(start_pos);
		start_pos.x += 0.3f;
		start_pos.z += 0.01f;
		aster->SetCollideFlag(true);

		AsteroidCollection.push_back(aster);
		Game.GetScene().AddObject(aster, GameObject::OBJECT_TYPE::ASTEROID);
	}
}

