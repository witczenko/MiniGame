#include "Animation.h"
#include <stdlib.h>

CSpriteAnimation::CSpriteAnimation() : 
CSprite(),
is_loaded(false),
anim_time(),
current_frame(0),
frame_time(33)
{
	type = OBJECT_TYPE::SPRITE_ANIM;
}

CSpriteAnimation::CSpriteAnimation(glm::vec3 pos, float32 width, float32 height, uint32 textureId) :
CSprite(pos, width, height, textureId),
is_loaded(false),
anim_time(),
current_frame(0),
frame_time(33)
{
	type = OBJECT_TYPE::SPRITE_ANIM;
}


CSpriteAnimation::~CSpriteAnimation()
{
}

uint32 CSpriteAnimation::GetFrame() const{
	return anim_data.start_tex + current_frame;
}

void CSpriteAnimation::SetAnimation(AnimTexData anim_data){
	this->anim_data = anim_data;
}

void CSpriteAnimation::SetFPS(uint32 fps){
	frame_time = 1000 / fps;
}

void CSpriteAnimation::Update(uint32 dt){
	anim_time += dt;
	if (anim_time > frame_time){
		if (current_frame < (anim_data.count)-1)
			current_frame++;
		else
			current_frame = 0;
		anim_time = 0;
	}

	this->AssingTexture(anim_data.start_tex+current_frame);
}

AnimTexData CSpriteAnimation::GetAnimation()
{
	return anim_data;
}