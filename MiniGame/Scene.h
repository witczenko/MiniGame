#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "GameObject.h"
#include "Types.h"
#include "Sprite.h"

class CScene
{
private:
	std::vector<GameObject*> ObjectCollection[GameObject::TYPE_COUNT];
	std::vector<GameObject*> CollideObjects;

	CSpriteRenderer SpriteRenderer;
	std::vector<CSprite*> AnimSpriteCollection;

	void cleanUp();
	void proccessCollision();

public:
	void AddObject(GameObject* obj, GameObject::OBJECT_TYPE type);
	void Draw();
	void Init();
	void Update(uint32 dt);
	CScene();
	~CScene();
};

#endif // SCENE_H