#ifndef _FRUSTUMR_
#define _FRUSTUMR_

#include "GameUtils.h"
#include "Plane.h"

class FrustumR 
{
private:
	enum {
		TOP = 0,
		BOTTOM,
		LEFT,
		RIGHT,
		NEARP,
		FARP
	};

public:
	static enum {OUTSIDE, INTERSECT, INSIDE};

	Plane pl[6];


	glm::vec3 ntl,ntr,nbl,nbr,ftl,ftr,fbl,fbr,X,Y,Z,camPos;
	float nearD, farD, ratio, angle;
	float sphereFactorX, sphereFactorY;
	float tang;
	float nw,nh,fw,fh;

	FrustumR::FrustumR();
	FrustumR::~FrustumR();

	void setFrustum(const glm::mat4x4 & mat);
	//int pointInFrustum(glm::vec3 &p);
	int sphereInFrustum(glm::vec3 &p, float radius);
	//int boxInFrustum(AABox &b);
};


#endif