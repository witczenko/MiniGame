#ifndef SCENE_H
#define SCENE_H

#include "GameUtils.h"
#include "GameObject.h"
#include "Sprite.h"

class CPlayer;
class CGame;

class CScene
{
	friend class CGame;

private:
	struct pending_obj_t{
		GameObject* obj;
		GameObject::OBJECT_TYPE type;
		pending_obj_t(GameObject* in_obj, GameObject::OBJECT_TYPE in_type) : obj(in_obj), type(in_type){};
	};

	std::vector<GameObject*> ObjectCollection[GameObject::TYPE_COUNT];
	std::vector<GameObject*> CollideObjects;
	std::vector<pending_obj_t> PendingObjects;

	/* Flag indicates if we are in section where we use object collection (ObjectCollection, CollideObjects). 
	   If we iterate through collection, we can't insert into new objects (e.g. Object want add somethig to Scene in function update or OnCollission),
	   When flag is true, new objects are added to the PendingObjects vector and after critical section added normally to scene.
	*/
	bool critical_section;
	CSpriteRenderer SpriteRenderer;
	std::vector<CSprite*> AnimSpriteCollection;
	CPlayer *player;

	void cleanUp();
	void proccessCollision();
	void Draw();
	void Init();
	void Update(uint32 dt);

public:
	void AddObject(GameObject* obj, GameObject::OBJECT_TYPE type);
	
	CScene();
	~CScene();
};

#endif // SCENE_H