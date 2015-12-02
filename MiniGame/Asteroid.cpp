#include "Asteroid.h"

static const int32 BASE_DURABILITY = 100;


CAsteroid::CAsteroid()
{
	this->durability = BASE_DURABILITY + (rand() % 50);
}


CAsteroid::~CAsteroid()
{
}
