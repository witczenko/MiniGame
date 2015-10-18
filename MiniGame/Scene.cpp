#include "Scene.h"
#include <glm\glm.hpp>
#include "Animation.h"

glm::vec3 AnimInitPos(0.0f, 0.0f, 0.0f);

CScene::CScene()
{
}


CScene::~CScene()
{
	cleanUp();
}

void CScene::Init(){
	SpriteRenderer.Init();
}

void CScene::AddObject(GameObject* obj, GameObject::OBJECT_TYPE type){
	ObjectCollection[type].push_back(obj);

	switch (type){
	case GameObject::SPRITE:{
					SpriteRenderer.AddSprite((CSprite*)obj);
	}
	case GameObject::SPRITE_ANIM:{
						 CSprite *s = (CSprite*)obj;
						 SpriteRenderer.AddSprite(s);
	}
	}
}

void CScene::Draw(){
	//sprite rendering
	SpriteRenderer.Render();
}



void CScene::Update(uint32 dt){
	for (auto spriteAnim : ObjectCollection[GameObject::SPRITE_ANIM]){
		CSpriteAnimation *sa = (CSpriteAnimation*)spriteAnim;
		sa->Update(dt);
	}
}

void CScene::cleanUp(){
	//delete all game objects 
	for (int i = 0; i < GameObject::TYPE_COUNT; i++)
	{
		switch (i){
		case GameObject::SPRITE:{
									for (auto sprite : ObjectCollection[GameObject::SPRITE]){
										CSprite *s = (CSprite*)sprite;
										delete s;
									}
									ObjectCollection[GameObject::SPRITE].clear();
									break;
		}
		case GameObject::SPRITE_ANIM:{
										 for (auto spriteAnim : ObjectCollection[GameObject::SPRITE]){
											 CSpriteAnimation *sa = (CSpriteAnimation*)spriteAnim;
											 delete sa;
										 }
										 ObjectCollection[GameObject::SPRITE].clear();
										 break;
		}





		}
	}
}
