#include "TextureManager.h"
#include <stdlib.h>


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
	LoadTexture("gfx/skybox/skybox1/1.png");
	LoadTexture("gfx/Spaceship_art_pack/Background/background.jpg");

	//here you can load animations!
	LoadAnimation("gfx/Spaceship_art_pack/Blue/Animation/", 8);
	LoadAnimation("gfx/energy_ball/blue/keyframes/", 6);
	LoadAnimation("gfx/energy_ball/pink/keyframes/", 6);
	LoadAnimation("gfx/Spaceship_art_pack/Red/Enemy_animation/", 9);
	LoadAnimation("gfx/Spaceship_art_pack/Blue/Enemy_animation/", 4);

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

bool CTextureManager::LoadAnimation(const std::string & prefix, uint32 count){
	std::string texture_name;
	AnimTexData anim_data;
	char number[10];
	uint32 loaded = 0;

	anim_data.count = count;

	for (uint32 i = 0; i < count; i++)
	{
		sprintf(number, "%d", i + 1);
		texture_name = prefix + number + ".png";
		uint32 tex = VSResourceLib::loadRGBATexture(texture_name);

		if (tex){
			if (i == 0) anim_data.start_tex = tex;	
			loaded++;
		}
		else{
			uint32  tex_id = anim_data.start_tex;
			for (uint32 j = anim_data.start_tex; j < (loaded + anim_data.start_tex); j++){
				glDeleteTextures(1, &tex_id);
				tex_id = j;
			}
			return false;
		}
	}

	animations[prefix] = anim_data;
	return true;
}

bool CTextureManager::GetAnimation(const std::string & prefix, AnimTexData &anim_data){
	auto anim = animations.find(prefix);
	if (anim != animations.end()){
		anim_data = anim->second;
		return true;
	}
	else 
		return false;
}