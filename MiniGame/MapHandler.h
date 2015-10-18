#pragma once
#ifndef MAPHANDLER_H
#define MAPHANDLER_H

/* 
	prototype of the map handling class
	work in progress
	daveman00
*/

#include "Types.h"
#include "Sprite.h"
#include "Scene.h"
#include "TextureManager.h"
#include <glm/glm.hpp>
#include <vector>

/*
	TODO
		Function Load_Map
			- loading txt(?) file with chars describing tiles


*/

class CTile : public CSprite
{
public:
	enum TILE_TYPE{
		NONE = 0,
		GRASS,
		ICE,
		WATER,
		FIRE
	};

	CTile();
	//CTile(CTile* kafel);
	CTile(TILE_TYPE type, uint32 row, uint32 col);
	TILE_TYPE getType();
	uint32 getRow();
	~CTile();
private:
	uint32 id;
	TILE_TYPE type;
	uint32 row;
	uint32 col;
};


class CMapHandler
{

	std::vector<CTile*> tile_map;
	//std::vector<char> txt_map;



public:
	CMapHandler();
	~CMapHandler();

	void LoadTxtMap( const char* filename);
	void AddToScene(CScene* scene, CTextureManager* texutreMan);
	//void AddTile();
	void DisplayTiles();
};


#endif // MAPHANDLER_H