#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "GameObject.h"
#include "Types.h"
#include "Sprite.h"

class CScene
{
	friend class CGame;

private:
	std::vector<GameObject*> ObjectCollection[GameObject::TYPE_COUNT];
	std::vector<GameObject*> CollideObjects;

	CSpriteRenderer SpriteRenderer;
	std::vector<CSprite*> AnimSpriteCollection;

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