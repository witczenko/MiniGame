#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include "types.h"



class CCamera
{
private:
	glm::vec3 Position;
	glm::vec3 Target;
	glm::mat4x4 Projection;
	glm::mat4x4 View;

	float32 fov, aspect, znear, zfar;

public:
	CCamera(float32 fov, float32 aspect, float32 znear, float32 zfar);
	~CCamera();

	/* Setters */
	glm::vec3 GetPosition() const;
	glm::mat4x4 GetProjection() const;
	glm::mat4x4 GetView() const;
	glm::vec3 GetTarget() const;

	/* Getters */
	void SetFov(float32 fov);
	void SetAspect(float32 aspect);
	void SetPosition(glm::vec3 pos);
	void SetTarget(glm::vec3 target);

};

#endif

