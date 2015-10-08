#include "GameUtils.h"

GameUtils::GameUtils()
{
}


GameUtils::~GameUtils()
{
}

float  GameUtils::GetEulerDist3f(float *posA, float *posB)
{
	return hypot(hypot(posA[0] - posB[0], posA[1] - posB[1]), posA[2] - posB[2]);
}

bool GameUtils::RayVsAABB(glm::vec3 rayDir, glm::vec3 rayOrg, glm::vec3 min, glm::vec3 max){
	glm::vec3 dirfrac;
	float t;

	// r.dir is unit direction vector of ray
	dirfrac.x = 1.0f / rayDir.x;
	dirfrac.y = 1.0f / rayDir.y;
	dirfrac.z = 1.0f / rayDir.z;
	// lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
	// r.org is origin of ray
	float t1 = (min.x - rayOrg.x)*dirfrac.x;
	float t2 = (max.x - rayOrg.x)*dirfrac.x;
	float t3 = (min.y - rayOrg.y)*dirfrac.y;
	float t4 = (max.y - rayOrg.y)*dirfrac.y;
	float t5 = (min.z - rayOrg.z)*dirfrac.z;
	float t6 = (max.z - rayOrg.z)*dirfrac.z;

	float tmin = MAX(MAX(MIN(t1, t2), MIN(t3, t4)), MIN(t5, t6));
	float tmax = MIN(MIN(MAX(t1, t2), MAX(t3, t4)), MAX(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
	if (tmax < 0)
	{
		t = tmax;
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		t = tmax;
		return false;
	}

	t = tmin;
	return true;
}

glm::vec3 GameUtils::CalcCamRay(glm::vec2 normMouse, glm::mat4x4 projMat, glm::mat4x4 viewMat){
	glm::vec4 mouse_clip = glm::vec4(normMouse.x, normMouse.y, -1.0, 1.0);
	glm::vec4 ray_eye = glm::inverse(projMat) * mouse_clip;
	ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
	return glm::normalize(glm::vec3(glm::inverse(viewMat) * ray_eye));
}

glm::vec3 GameUtils::ScaleToUnit(glm::vec3 inVec){
	float max = fabs(inVec.x);
	max = MAX(max, fabs(inVec.y));
	max = MAX(max, fabs(inVec.z));

	return (inVec / max);
}