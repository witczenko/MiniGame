#include "Scene.h"
#include <glm\glm.hpp>
#include "Animation.h"
#include "Player.h"

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
						break;
	}
	case GameObject::SPRITE_ANIM:{
						CSprite *s = (CSprite*)obj;
						SpriteRenderer.AddSprite(s);
						break;
	}
	case GameObject::TILE:{
						CSprite *s = (CSprite*)obj;
						SpriteRenderer.AddSprite(s);
						break;
	}
	case GameObject::PLAYER:{
						CPlayer *s = (CPlayer*)obj;
						SpriteRenderer.AddSprite((CSprite*)s->sprite_anim);
						ObjectCollection[GameObject::SPRITE_ANIM].push_back(s->sprite_anim);
						break;
	}
	}
}

void CScene::Draw(){
	//sprite rendering
	SpriteRenderer.Render();
}



void CScene::Update(uint32 dt){
	for (uint32 i = 0; i < GameObject::TYPE_COUNT; i++){
		for (auto obj : ObjectCollection[i]){
			obj->Update(dt);
		}
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
		case GameObject::PLAYER:{
									//TODO Delete player
									/* 
									for (auto player : ObjectCollection[GameObject::PLAYER]){
										CSpriteAnimation *pl = (CSpriteAnimation*)player;
										delete pl;
									}
									ObjectCollection[GameObject::PLAYER].clear();
									*/
									break;
		}





		}
	}
}
