#ifndef TEXTURE_MANAGER_H 
#define TEXTURE_MANAGER_H

#include <map>
#include "Types.h"
#include <VSL\vsResourceLib.h>
#include <string>
#include "Animation.h"


class CTextureManager
{
public:
	CTextureManager();
	~CTextureManager();

	void Init();
	bool LoadTexture(const std::string & name);
	bool LoadAnimation(const std::string & prefix, uint32 count);
	void UnloadTexture(const std::string & name);

	uint32 GetTexture(const std::string & name);
	bool GetAnimation(const std::string & prefix, AnimTexData &anim_data);

private:
	std::map<std::string, uint32> textures;
	std::map<std::string, AnimTexData> animations;
};

#endif 