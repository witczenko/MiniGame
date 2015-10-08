#ifndef TEXTURE_MANAGER_H 
#define TEXTURE_MANAGER_H

#include <map>
#include "Types.h"
#include <VSL\vsResourceLib.h>
#include <string>


class CTextureManager
{
public:
	CTextureManager();
	~CTextureManager();

	void Init();
	bool LoadTexture(const std::string & name);
	void UnloadTexture(const std::string & name);

	uint32 GetTexture(const std::string & name);

private:
	std::map<std::string, uint32> textures;
};

#endif 