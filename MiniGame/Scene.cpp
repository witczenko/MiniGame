#include "Scene.h"
#include <glm\glm.hpp>
#include "Animation.h"
#include "Player.h"
#include "Mob.h"

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

	if (obj->GetCollideFlag())
		CollideObjects.push_back(obj);

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
	case GameObject::PLAYER:
	{
						CPlayer *s = (CPlayer*)obj;
						SpriteRenderer.AddSprite((CSprite*)s->sprite_anim);
						ObjectCollection[GameObject::SPRITE_ANIM].push_back(s->sprite_anim);
						break;
	}
	case GameObject::MOB:
	{
							CMob *s = (CMob*)obj;
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
	proccessCollision();

	//Error when we don't create a Player!
	GameObject *player = ObjectCollection[GameObject::OBJECT_TYPE::PLAYER][0];

	for (uint32 i = 0; i < GameObject::TYPE_COUNT; i++){
		for (auto obj : ObjectCollection[i]){
			if (i == GameObject::OBJECT_TYPE::MOB){
				((CMob*)obj)->setTarget(player->GetPos());
			}
			obj->Update(dt);
		}
	}
}

void CScene::cleanUp(){
	//delete all game objects 
	for (size_t i = 0; i < GameObject::OBJECT_TYPE::TYPE_COUNT; i++)
	{
		for (auto obj : ObjectCollection[i]){
			if (obj){
				delete obj;
				obj = NULL;
			}
		}
		ObjectCollection[i].clear();
	}
}

void CScene::proccessCollision(){
	for (auto obj1 : CollideObjects){
		for (auto obj2 : CollideObjects)
		{
			if (obj1 == obj2)
				continue;

			glm::vec2 obj12_vec;
			obj12_vec = glm::vec2(obj2->GetPos()) - glm::vec2(obj1->GetPos());
			
			if (glm::length(obj12_vec) < (obj1->GetCollisionRad() + obj2->GetCollisionRad())){
				obj1->OnCollision(obj2);
				obj2->OnCollision(obj1);
			}

		}
	}
}
