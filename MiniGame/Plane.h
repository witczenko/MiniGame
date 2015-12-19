#ifndef _PLANE_
#define _PLANE_
#include "GameUtils.h"

class Plane  
{
public:
	glm::vec3 normal, point;
	float d;
	Plane::Plane(void);
	Plane::~Plane();

	void setCoefficients(const glm::vec4 & vec);
	float distance(glm::vec3 &p);
};


#endif