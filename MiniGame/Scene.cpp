#include "Scene.h"
#include "Animation.h"
#include "Mob.h"
#include "Asteroid.h"
#include "Game.h"
#include "Projectile.h"


CScene::CScene():
player(NULL)
{
}

CScene::~CScene()
{
	cleanUp();
}

void CScene::Init(){
	SpriteRenderer.Init();
	critical_section = false;
}

void CScene::AddObject(GameObject* obj, GameObject::OBJECT_TYPE type){
	if (!obj || type == GameObject::OBJECT_TYPE::UNDEFINED)
		return;

	if (critical_section){
		PendingObjects.push_back(pending_obj_t(obj, type));
		return;
	}

	ObjectCollection[type].push_back(obj);
	GeneralCollection.push_back(obj);

	if (obj->GetCollideFlag())
		CollideObjects.push_back(obj);

	switch (type){
	case GameObject::SPRITE:{
						ObjectCollection[GameObject::SPRITE].push_back((CSprite*)obj);
						break;
	}
	case GameObject::SPRITE_ANIM:{
						CSprite *s = (CSprite*)obj;
						ObjectCollection[GameObject::SPRITE].push_back(s);
						break;
	}
	case GameObject::TILE:{
						CSprite *s = (CSprite*)obj;
						ObjectCollection[GameObject::SPRITE].push_back(s);
						break;
	}
	case GameObject::PLAYER:
	{
						CPlayer *s = (CPlayer*)obj;
						player = s;
						ObjectCollection[GameObject::SPRITE].push_back((CSprite*)s->sprite_anim);
						ObjectCollection[GameObject::SPRITE_ANIM].push_back(s->sprite_anim);
						break;
	}
	case GameObject::MOB:
	{
						CMob *s = (CMob*)obj;
						ObjectCollection[GameObject::SPRITE].push_back((CSprite*)s->sprite_anim);
						ObjectCollection[GameObject::SPRITE_ANIM].push_back(s->sprite_anim);
						break;
	}
	case GameObject::ASTEROID:{
								  CAsteroid *aster = (CAsteroid*)obj;
								  ObjectCollection[GameObject::SPRITE].push_back(aster->sprite);
								  break;
	}
	case GameObject::PROJECTILE:
	{
						CProjectile *s = (CProjectile*)obj;
						ObjectCollection[GameObject::SPRITE].push_back((CSprite*)s->sprite_anim);
						ObjectCollection[GameObject::SPRITE_ANIM].push_back(s->sprite_anim);
						break;
	}
	default:
	{

	}
	}
}

void CScene::Draw(){
	char buffor[64];

	//sprite renderie
	VisibleSprites.clear();
	for (auto sprite : ObjectCollection[GameObject::SPRITE]){
		if (sprite->status == GameObject::OBJECT_STATUS::ALIVE){
			CSprite* sp = (CSprite*)sprite;
			if (CGame::GetGameInstance().GetCamera().SphereFrustumTest(sp->GetPos(), sp->GetCollisionRad()) != FrustumR::OUTSIDE)
				VisibleSprites.push_back(sp);
		}
	}
	sprintf(buffor, "Visible objects: %d\n", VisibleSprites.size());

	//Frustum culling
	CGame::GetGameInstance().GetRenderLog() += buffor;
	SpriteRenderer.Render(VisibleSprites);
}



void CScene::Update(uint32 dt){
	if (player){
		glm::vec3 newCamPos = player->GetPos();
		newCamPos.z = CGame::GetGameInstance().GetCamera().GetPosition().z;

		CGame::GetGameInstance().GetCamera().SetPosition(newCamPos);
		CGame::GetGameInstance().GetCamera().SetTarget(player->GetPos());
	}

	critical_section = true;
	proccessCollision();

	//Error when we don't create a Player!
	for (uint32 i = 0; i < GameObject::TYPE_COUNT; i++){
		for (auto obj : ObjectCollection[i]){
			if (i == GameObject::OBJECT_TYPE::MOB){
				if (player)
					((CMob*)obj)->setTarget(player->GetPos());
			}

			if (obj && obj->status == GameObject::OBJECT_STATUS::ALIVE){
				obj->Update(dt);
			}
			
		}
	}
	critical_section = false;

	for (auto pobj : PendingObjects)
		this->AddObject(pobj.obj, pobj.type);

	PendingObjects.clear();
}

void CScene::cleanUp(){
	//delete all game objects 
		for (auto obj : GeneralCollection){
			if (obj){
				delete obj;
				obj = NULL;
			}
		}
		GeneralCollection.clear();
}

void CScene::proccessCollision(){
	for (auto obj1 : CollideObjects){
		for (auto obj2 : CollideObjects)
		{
			if (obj1->status != GameObject::OBJECT_STATUS::ALIVE || obj2->status != GameObject::OBJECT_STATUS::ALIVE)
				continue;

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

void CScene::frustumCulling(){
}
