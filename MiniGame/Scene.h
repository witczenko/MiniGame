#pragma once
#include <vector>
#include "GameObject.h"
#include "Types.h"
#include "Sprite.h"

class CScene
{
private:
	std::vector<GameObject*> ObjectCollection[GameObject::TYPE_COUNT];
	CSpriteRenderer SpriteRenderer;
	std::vector<CSprite*> AnimSpriteCollection;

	void cleanUp();
public:
	void AddObject(GameObject* obj, GameObject::OBJECT_TYPE type);
	void Draw();
	void Init();
	void Update(uint32 dt);
	CScene();
	~CScene();
};

