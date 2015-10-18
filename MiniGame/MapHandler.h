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
#include <glm/glm.hpp>
#include <vector>

/*
	TODO
		Function Load_Map
			- loading txt(?) file with chars describing tiles


*/

class CTile
{
	uint32 id;
	char type;
	glm::vec3 pos;
	uint32 row;
	uint32 col;

public:
	CTile();
	//CTile(CTile* kafel);
	CTile(char type, uint32 row, uint32 col);
	char getType();
	uint32 getRow();
	~CTile();
};


class CMapHandler
{

	std::vector<CTile*> tile_map;
	//std::vector<char> txt_map;



public:
	CMapHandler();
	~CMapHandler();

	void LoadTxtMap( const char* filename);
	//void AddTile();
	void DisplayTiles();
};


#endif // MAPHANDLER_H