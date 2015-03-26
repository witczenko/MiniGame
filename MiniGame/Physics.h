#ifndef PHYSICS_C
#define PHYSICS_C

#include <Box2D\Box2D.h>
#include <vector>
#include "Types.h"
#include "Sprite.h"
#include <thread>
#include <mutex>

class CPhysicalObject;

class CPhysics
{	
public:
	CPhysics();
	~CPhysics();

	void AddPhysicalObject(CPhysicalObject *object);
	void DeleteJoint(b2Joint *joint);

	b2Body *GetBodyAtMouse(glm::vec2 mousePos);
	b2MouseJoint* CPhysics::createMouseJoint(b2Body* body);
	b2World *GetBox2dWorld() const;

	/* Use this function to block physics thread f.g if you want to draw
	physics objects.
	*/
	void Lock();
	void Unlock();

private:
	b2World *boxWorld;
	b2Body* groundBody;

	float32 timeStep;
	int32 velocityIterations;
	int32 positionIterations;
	uint32 timeAcc;
	std::vector<CPhysicalObject*> objects;

	/* Thread stuff */
	std::thread physicsThread;
	std::mutex physics_mutex;
	bool do_simulation;

	void threadPhysicsUpdate();
	void Update(uint32 dt);
};


/* */
class CPhysicalObject : public CSprite {
	friend CPhysics;

private:
	b2Body *body;
	float32 mass;
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape dynamicBox;
public:
	CPhysicalObject(glm::vec3 pos, GLfloat width, GLfloat height, CTexture *Texture, CShaderProgram* pShaderProgram);
	virtual ~CPhysicalObject();
};


class MyQueryCallback : public b2QueryCallback {
public:
	std::vector<b2Fixture*> foundFixtures;

	bool ReportFixture(b2Fixture* fixture) {
		foundFixtures.push_back(fixture);
		return true;
	}
};
#endif //PHYSICS_C
