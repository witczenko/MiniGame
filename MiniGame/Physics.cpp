#include "Physics.h"
#include "SDL.h"

#define TIME_STEP		(1.0f / 60.0f)
#define GROUND_Y_POS	(-10.0f) 
#define GRAVITY			(-10.0f)



CPhysics::CPhysics() : 
boxWorld(NULL),
timeStep(TIME_STEP),
velocityIterations(6),
positionIterations(2),
timeAcc(0),
do_simulation(true)
{
	// Define the gravity vector.
	b2Vec2 gravity(0.0f, GRAVITY);

	// Construct a world object, which will hold and simulate the rigid bodies.
	boxWorld = new b2World(gravity);
	

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, GROUND_Y_POS);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	groundBody = boxWorld->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(50.0f, 10.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Define the dynamic body. We set its position and call the body factory.


	/* Begin simulation thread  */
	do_simulation = true;
	physicsThread = std::thread(std::bind(&CPhysics::threadPhysicsUpdate, this));


}

CPhysics::~CPhysics()
{
	do_simulation = false;
	physicsThread.join();

	delete boxWorld;
}

void CPhysics::threadPhysicsUpdate(){
	uint32 CurrentTime = 0;
	while (do_simulation){
		//Time stuff
		uint32 OldTime = CurrentTime;
		CurrentTime = SDL_GetTicks();
		uint32 dt = (CurrentTime - OldTime);

		physics_mutex.lock();
		this->Update(dt);
		physics_mutex.unlock();

		SDL_Delay(1);
	}
}


void CPhysics::Update(uint32 dt){

	timeAcc += dt;

	/* update physics with fixed step size -> 60 fps */
	if (timeAcc >= timeStep * 1000){
		timeAcc = 0;

		boxWorld->Step(timeStep, velocityIterations, positionIterations);
		boxWorld->ClearForces();

		for (auto it_object = objects.begin(); it_object != objects.end(); it_object++){
			b2Body *objBody = (*it_object)->body;
			(*it_object)->SetPos(glm::vec3(objBody->GetPosition().x, objBody->GetPosition().y, (*it_object)->Pos.z));
			(*it_object)->Rotatef(objBody->GetAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
		}

	}

	return;
}

void CPhysics::Lock(){
	physics_mutex.lock();
}

void CPhysics::Unlock(){
	physics_mutex.unlock();
}


void CPhysics::AddPhysicalObject(CPhysicalObject *object){
	physics_mutex.lock();
	object->body = boxWorld->CreateBody( &(object->bodyDef));
	object->body->CreateFixture( &(object->fixtureDef));
	objects.push_back(object);
	physics_mutex.unlock();
}

b2World *CPhysics::GetBox2dWorld() const{
	return boxWorld;
}

b2MouseJoint* CPhysics::createMouseJoint(b2Body* body)
{
	physics_mutex.lock();
	b2MouseJointDef md;
	md.bodyA = groundBody;
	md.bodyB = body;
	md.maxForce = 400.0f * body->GetMass();
	md.frequencyHz = 60;
	md.collideConnected = true;
	//md.dampingRatio = 0.1;
	body->SetAwake(true);
	b2MouseJoint* joint = (b2MouseJoint*)boxWorld->CreateJoint(&md);

	physics_mutex.unlock();
	return joint;
}


b2Body* CPhysics::GetBodyAtMouse(glm::vec2 mousePos)
{

	physics_mutex.lock();
	b2Vec2 b2mousePos;

	b2mousePos.x = mousePos.x;
	b2mousePos.y = mousePos.y;

	b2AABB MouseArea;
	MouseArea.lowerBound.Set(mousePos.x - 0.001, mousePos.y - 0.001);
	MouseArea.upperBound.Set(mousePos.x + 0.001, mousePos.y + 0.001);
	
	b2Body* BodyBuffer = NULL;
	MyQueryCallback callback;

	//Checking area for bodies

	boxWorld->QueryAABB(&callback, MouseArea);
	

	for (uint32 i = 0; i < callback.foundFixtures.size(); i++)
	{
		if (callback.foundFixtures[i]->TestPoint(b2mousePos) && callback.foundFixtures[i]->GetBody()->GetType() == b2_dynamicBody)
		{
			BodyBuffer = callback.foundFixtures[i]->GetBody();
			break;
		}
	}

	physics_mutex.unlock();

	return BodyBuffer;
}

void CPhysics::DeleteJoint(b2Joint *joint){
	physics_mutex.lock();
	boxWorld->DestroyJoint(joint);
	physics_mutex.unlock();
}





/* CPhysicalObject */

CPhysicalObject::CPhysicalObject(glm::vec3 pos, GLfloat width, GLfloat height, CTexture *Texture, CShaderProgram* pShaderProgram):
CSprite(pos, width, height, Texture, pShaderProgram),
body(NULL),
mass(1.0f)

{	
	
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set( Pos.x, Pos.y);

	// Define another box shape for our dynamic body.
	dynamicBox.SetAsBox(Width / 2.0f - 0.01f, Height / 2.0f - 0.01f);

	// Define the dynamic body fixture.
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 1.3f;
	
};

CPhysicalObject::~CPhysicalObject(){

}


