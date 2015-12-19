#include "FrustumR.h"
#include <glm/gtc/matrix_access.hpp>
#include <math.h>
#include <stdio.h>

#define HALF_ANG2RAD 3.14159265358979323846/360.0 

FrustumR::FrustumR() {}

FrustumR::~FrustumR() {}

#define m(col,row)  m[row*4+col]


void FrustumR::setFrustum(const glm::mat4x4 & mat) {
	glm::vec4 rowX = glm::row(mat, 0);
	glm::vec4 rowY = glm::row(mat, 1);
	glm::vec4 rowZ = glm::row(mat, 2);
	glm::vec4 rowW = glm::row(mat, 3);
 
	pl[NEARP].setCoefficients(rowW + rowX);
	pl[FARP].setCoefficients(rowW - rowX);
	pl[BOTTOM].setCoefficients(rowW + rowY);
	pl[TOP].setCoefficients(rowW - rowY);
	pl[LEFT].setCoefficients(rowW + rowZ);
	pl[RIGHT].setCoefficients(rowW - rowZ);

}

#undef M


/*
int FrustumR::pointInFrustum(glm::vec3 &p) {

	float pcz,pcx,pcy,aux;

	// compute vector from camera position to p
	glm::vec3 v = p-camPos;

	// compute and test the Z coordinate
	pcz = v.innerProduct(-Z);
	if (pcz > farD || pcz < nearD)
		return(OUTSIDE);

	// compute and test the Y coordinate
	pcy = v.innerProduct(Y);
	aux = pcz * tang;
	if (pcy > aux || pcy < -aux)
		return(OUTSIDE);
		
	// compute and test the X coordinate
	pcx = v.innerProduct(X);
	aux = aux * ratio;
	if (pcx > aux || pcx < -aux)
		return(OUTSIDE);


	return(INSIDE);

	
}
*/

int FrustumR::sphereInFrustum(glm::vec3 &p, float radius) {
	float distance;
	int result = INSIDE;

	for (int i = 0; i < 6; i++) {
		distance = pl[i].distance(p);
		if (distance < -radius)
			return OUTSIDE;
		else if (distance < radius)
			result = INTERSECT;
	}
	return(result);
}

