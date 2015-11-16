#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include <glm\glm.hpp>
#include <VSL\vslibs.h>
#include "Types.h"

#define MIN(a,b)            (((a) < (b)) ? (a) : (b))
#define MAX(a,b)            (((a) > (b)) ? (a) : (b))
#define D2R(x) x*(3.141592f/180.0f)
#define R2D(x) x*57.2957795

class GameUtils
{
public:
	GameUtils();
	~GameUtils();
	
	static float GetEulerDist3f(float *posA, float *posB);
	//Test Ray vs box (!axis aligned) collision 
	static bool RayVsAABB(glm::vec3 rayDir, glm::vec3 rayOrg, glm::vec3 min, glm::vec3 max);
	//Calculate direction of vector camera -> mouse 
	static glm::vec3 CalcCamRay(glm::vec2 normMouse, glm::mat4x4 projMat, glm::mat4x4 viewMat);
	//normalize vector (divide by max component)
	static glm::vec3 ScaleToUnit(glm::vec3 inVec);

	static void NormalizeMousePos(uint32 screenWidth, uint32 screenHeight, uint32 inX, uint32 inY, float32 &outX, float32 &outY);
};

#endif

