#ifndef ANIMATION_H
#define ANIMATION
#include "Sprite.h"

/* Sprite animation */
class CSprtieAnimation : public CSprite
{
public:
	CSprtieAnimation();
	~CSprtieAnimation();

	uint32 GetFrame() const; //return texture ID 
	bool LoadAnimation(const std::string & prefix, uint32 size);
	void SetFPS(uint32 fps);
	void Update(uint32 dt);

private:
	uint32 *frames;
	uint32 loaded_frames;
	uint32 current_frame;
	uint32 anim_time;
	uint32 frame_time;

	bool is_loaded;

	void cleanUp();
};

#endif
