#include "Animation.h"
#include <stdlib.h>

CSpriteAnimation::CSpriteAnimation() : 
CSprite(),
is_loaded(false),
loaded_frames(0),
anim_time(),
current_frame(0),
frame_time(33)
{
	type = OBJECT_TYPE::SPRITE_ANIM;
}

CSpriteAnimation::CSpriteAnimation(glm::vec3 pos, float32 width, float32 height, uint32 textureId) :
CSprite(pos, width, height, textureId),
is_loaded(false),
loaded_frames(0),
anim_time(),
current_frame(0),
frame_time(33)
{
	type = OBJECT_TYPE::SPRITE_ANIM;
}


CSpriteAnimation::~CSpriteAnimation()
{
	cleanUp();
}

uint32 CSpriteAnimation::GetFrame() const{
	return frames[current_frame];
}

bool CSpriteAnimation::LoadAnimation(const std::string & prefix, uint32 size){
	std::string texture_name;
	char number[10];
	
	frames = new uint32[size];

	for (uint32 i =	0; i < size; i++)
	{
		sprintf(number, "%d", i+1);
		texture_name = prefix + number + ".png";

		uint32 tex = VSResourceLib::loadRGBATexture(texture_name);
		if (tex){
			frames[i] = tex;
			loaded_frames++;
		}
		else{
			cleanUp();
			return false;
		}
	}

	return true;
}

void CSpriteAnimation::SetFPS(uint32 fps){
	frame_time = 1000 / fps;
}

void CSpriteAnimation::Update(uint32 dt){
	anim_time += dt;
	if (anim_time > frame_time){
		if (current_frame < loaded_frames-1)
			current_frame++;
		else
			current_frame = 0;


		anim_time = 0;
	}

	this->AssingTexture(frames[current_frame]);

}

void CSpriteAnimation::cleanUp(){
	for (uint32 i = 0; i < loaded_frames; i++){
		glDeleteTextures(1, &frames[i]);
	}
	delete[] frames;

	loaded_frames = 0;
}