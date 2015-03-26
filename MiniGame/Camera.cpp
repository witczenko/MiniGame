#include "Camera.h"
#include <glm\gtx\matrix_operation.hpp>
#include "glm\gtx\transform.hpp"

CCamera::CCamera(float32 fov, float32 aspect, float32 znear, float32 zfar) :
Position(glm::vec3(0.0f, 0.0f, 4.0f)),
Target(glm::vec3(0.0f, 0.0f, 0.0f)),
fov(fov),
znear(znear),
zfar(zfar),
aspect(aspect)
{
	Projection = glm::perspective(fov, aspect, znear, zfar);
	View = glm::lookAt(Position, Target, glm::vec3(0.0f, 1.0f, 0.0f));
}


CCamera::~CCamera()
{
}


/* Getters */
glm::mat4x4 CCamera::GetProjection() const{
	return Projection;
}

glm::vec3 CCamera::GetPosition() const{
	return Position;
}

glm::mat4x4 CCamera::GetView() const{
	return View;
}

glm::vec3 CCamera::GetTarget() const{
	return Target;
}


/* Setters */
void CCamera::SetPosition(glm::vec3 pos){
	Position = pos;
	View = glm::lookAt(Position, Target, glm::vec3(0.0f, 1.0f, 0.0f));
}


void CCamera::SetAspect(float32 aspect){
	this->aspect = aspect;
	Projection = glm::perspective(fov, aspect, 0.1f, 200.0f);
}

void CCamera::SetFov(float32 fov){
	this->fov= fov;
	Projection = glm::perspective(fov, aspect, 0.1f, 200.0f);
}

void CCamera::SetTarget(glm::vec3 target){
	this->Target = target;
	View = glm::lookAt(Position, Target, glm::vec3(0.0f, 1.0f, 0.0f));
}