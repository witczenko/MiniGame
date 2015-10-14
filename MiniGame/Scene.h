#pragma once
#include <vector>
#include "GameObject.h"
#include "Types.h"
#include "Sprite.h"

class CScene
{
private:
	std::vector<GameObject*> ObjectCollection[10];
	CSpriteRenderer SpriteRenderer;
	std::vector<CSprite*> AnimSpriteCollection;
public:
	void AddObject(GameObject* obj, OBJECT_TYPE type);
	void Draw();
	void Init();
	void Update(uint32 dt);
	CScene();
	~CScene();
};

