#include "Animation.h"
#include <stdlib.h>

CSprtieAnimation::CSprtieAnimation() : 
CSprite(),
is_loaded(false),
loaded_frames(0),
anim_time(),
current_frame(0),
frame_time(33)
{
}


CSprtieAnimation::~CSprtieAnimation()
{
	cleanUp();
}

uint32 CSprtieAnimation::GetFrame() const{
	return frames[current_frame];
}

bool CSprtieAnimation::LoadAnimation(const std::string & prefix, uint32 size){
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

void CSprtieAnimation::SetFPS(uint32 fps){
	frame_time = 1000 / fps;
}

void CSprtieAnimation::Update(uint32 dt){
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

void CSprtieAnimation::cleanUp(){
	for (uint32 i = 0; i < loaded_frames; i++){
		glDeleteTextures(1, &frames[i]);
	}
	delete[] frames;

	loaded_frames = 0;
}