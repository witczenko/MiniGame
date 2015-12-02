#include "MapHandler.h"
//#include <fstream>

static const float32 TILE_W = 0.5f;
static const float32 TILE_H = 0.5f;

static uint32 TILE_COUNT = 0;

CTile::CTile()
{
	this->type = OBJECT_TYPE::TILE;

	id = TILE_COUNT;
	TILE_COUNT++;
	row = 0;
	col = 0;
	tile_type = NONE;
}

CTile::CTile(TILE_TYPE type, uint32 row, uint32 col)
{
	this->type = OBJECT_TYPE::TILE;

	id = TILE_COUNT;
	TILE_COUNT++;
	this->tile_type = type;
	this->row = row;
	this->col = col;
	this->SetPos(glm::vec3( (TILE_W*col)*2.0f, -(TILE_H*row)*2.0f, 0.0f ));
	this->SetWidth(TILE_W);
	this->SetHeight(TILE_H);

}

CTile::TILE_TYPE CTile::GetTileType()
{
	return tile_type;
}

uint32 CTile::GetRow()
{
	return row;
}

/*
CTile::CTile(CTile* kafel)
{
	id = TILE_COUNT;
	TILE_COUNT++;
	type = kafel->type;
	pos = kafel->pos;
} */

CTile::~CTile()
{
	TILE_COUNT--;
}

CMapHandler::CMapHandler()
{
	tile_map.clear();
}


CMapHandler::~CMapHandler()
{
	for (auto tile : tile_map)
		delete tile;
	tile_map.clear();
}

void CMapHandler::LoadTxtMap( const char* filename )
{
	/// txt variable
	std::ifstream mapa;

	/// opening the txt file
	mapa.open(filename, std::ifstream::in);

	/// checking the success of opening
	if (!mapa)
	{
		/// failure sets the flag
		printf("Could not load map from txt map.\n%s",filename);
	}
	else
	{	
		printf("Loading map: %s. Please wait.\n", filename);
		/// character handling variable
		char k;
		uint32 col = 0, row = 0;
		/// loops for loading characters from txt file
		
		while (!mapa.eof())
		{
			k = '\0';
			mapa.get(k);
			//printf("%c", k);

			switch (k)
			{
				case '\n':
				{
				    printf("\n");
					row++;
					col = 0;
					break;
				}
				case '\0':
				{
					break;
				}
				case '0':
					col++;
					break;
				case '1':
				{
							CTile *tile = new CTile(CTile::GRASS, row, col);
							tile->SetCollideFlag(true);
							tile_map.push_back(tile);
							col++;
							break;
				}
				case '2':
				{
							tile_map.push_back(new CTile(CTile::ICE, row, col));
							col++;
							break;
				}
				case '3':
				{
							tile_map.push_back(new CTile(CTile::WATER, row, col));
							col++;
							break;
				}
				case '4':
				{
							tile_map.push_back(new CTile(CTile::FIRE, row, col));
							col++;
							break;
				}
			}
			

		}


		/// closing the txt file
		mapa.close();
		printf("\nSuccessfully loaded map: %s\n", filename);
	}
}


void CMapHandler::DisplayTiles()
{
	uint32 r = 0;
	for (uint32 i = 0; i < TILE_COUNT; i++)
	{
		if ((tile_map[i]->GetRow()) != r)
		{
			printf("\n");
			r++;
		}
		printf("%d", tile_map[i]->GetTileType());
	}
}


void CMapHandler::AddToScene(CScene* scene, CTextureManager* texutreMan){
	for (auto tile : tile_map){
		switch (tile->GetTileType())
		{
		case CTile::GRASS: tile->AssingTexture(texutreMan->GetTexture("gfx/box.png"));
			break;
		case CTile::ICE: tile->AssingTexture(texutreMan->GetTexture("gfx/no_texture.png"));
			break;
		case CTile::FIRE: tile->AssingTexture(texutreMan->GetTexture("gfx/cursor.png"));
			break;
		default:
			break;
		}

		scene->AddObject(tile, GameObject::TILE);
	}
}
