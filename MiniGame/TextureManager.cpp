#include "TextureManager.h"


CTextureManager::CTextureManager()
{
}


CTextureManager::~CTextureManager()
{
	for (auto tex : textures){
		glDeleteTextures(1, &tex.second);
	}

	textures.clear();
}



void CTextureManager::Init(){
	//Here you can load texures!
	LoadTexture("gfx/no_texture.png");

	LoadTexture("gfx/smieja.png");
	LoadTexture("gfx/box.png");
	LoadTexture("gfx/cursor.png");
	LoadTexture("gfx/grid_color.png");
	LoadTexture("gfx/bg.jpg");
}

bool CTextureManager::LoadTexture(const std::string & name){
	auto tex = textures.find(name);
	if (tex == textures.end()){
		uint32 tex = VSResourceLib::loadRGBATexture(name);
		if (tex){
			textures[name] = tex;
			return true;
		}
	}

	return false;
}

void CTextureManager::UnloadTexture(const std::string & name){
	auto tex = textures.find(name);
	if (tex != textures.end()){
		glDeleteTextures(1, &tex->second);
		textures.erase(tex);
	}
}

uint32 CTextureManager::GetTexture(const std::string & name){
	auto tex = textures.find(name);
	if (tex != textures.end()){
		return tex->second;
	}
	else{
		return 0;
	}
}