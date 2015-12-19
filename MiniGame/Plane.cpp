// Plane.cpp
//
//////////////////////////////////////////////////////////////////////

#include "Plane.h"
#include <stdio.h>

Plane::Plane() {}

Plane::~Plane() {}


void Plane::setCoefficients(const glm::vec4 & vec) {

	// set the normal vector
	normal.x = vec.x;
	normal.y = vec.y;
	normal.z = vec.z;

	//compute the lenght of the vector
	float l = glm::length(normal);

	// normalize the vector
	normal = normal/l;

	// and divide d by th length as well
	this->d = vec.w/l;
}

float Plane::distance(glm::vec3 &p) {

	return (d + glm::dot(normal, p));
}

