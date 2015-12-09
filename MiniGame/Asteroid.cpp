#include "Asteroid.h"

static const int32 ASTEROID_BASE_DURABILITY = 100;
static const float32 ASTEROID_BASE_VELOCITY = 10.0f;


CAsteroid::CAsteroid():
sprite(NULL),
Game(CGame::GetGameIntance())
{
	this->type = OBJECT_TYPE::ASTEROID;
	this->durability = ASTEROID_BASE_DURABILITY + (rand() % 50);
	this->velocity = ASTEROID_BASE_VELOCITY + ((rand() % 10) - 5.0f);

	uint32 texId = Game.GetTextureManager().GetTexture("gfx/Spaceship_art_pack/Aestroids/aestroid_dark.png");
	sprite = new CSprite(glm::vec3(0.0f, 10.0f, 0.01f), 1.5f, 1.5f, texId);
}


CAsteroid::~CAsteroid()
{
}

void CAsteroid::Update(uint32 dt){
	float t = dt / 1000.0f;

}

