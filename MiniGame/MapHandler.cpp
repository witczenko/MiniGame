#include "MapHandler.h"
//#include <fstream>

static const uint8 TILE_W = 32;
static const uint8 TILE_H = 32;

static uint32 TILE_COUNT = 0;

CTile::CTile()
{
	id = TILE_COUNT;
	TILE_COUNT++;
	row = 0;
	col = 0;
	type = '0';
	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
}

CTile::CTile(char type, uint32 row, uint32 col )
{
	id = TILE_COUNT;
	TILE_COUNT++;
	this->type = type;
	this->row = row;
	this->col = col;
	glm::vec3 pos = glm::vec3( (TILE_W*col), (TILE_H*row), 0.0f );

}

char CTile::getType()
{
	return type;
}

uint32 CTile::getRow()
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
				default:
				{
					tile_map.push_back(new CTile(k, row, col));
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
		if ((tile_map[i]->getRow()) != r)
		{
			printf("\n");
			r++;
		}
		printf("%c", tile_map[i]->getType());
	}
}


