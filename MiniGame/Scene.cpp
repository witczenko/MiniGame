#include "Scene.h"
#include <glm\glm.hpp>
#include "Animation.h"

glm::vec3 AnimInitPos(0.0f, 0.0f, 0.0f);

CScene::CScene()
{
}


CScene::~CScene()
{
}

void CScene::Init(){
	SpriteRenderer.Init();
}

void CScene::AddObject(GameObject* obj, OBJECT_TYPE type){
	ObjectCollection[type].push_back(obj);

	switch (type){
	case SPRITE:{
					SpriteRenderer.AddSprite((CSprite*)obj);
	}
	case SPRITE_ANIM:{
						 CSprite *s = (CSprite*)obj;
						 SpriteRenderer.AddSprite(s);
	}
	}
}

void CScene::Draw(){
	//sprite rendering
	SpriteRenderer.Render();
	//animation rendering 
	for (auto spriteAnim : ObjectCollection[SPRITE_ANIM]){

	}
}



void CScene::Update(uint32 dt){
	for (auto spriteAnim : ObjectCollection[SPRITE_ANIM]){
		CSprtieAnimation *sa = (CSprtieAnimation*)spriteAnim;
		sa->Update(dt);
	}
}

