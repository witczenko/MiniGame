#ifndef ANIMATION_H
#define ANIMATION_H
#include "Sprite.h"

/* Sprite animation */
class CSpriteAnimation : public CSprite
{
public:
	CSpriteAnimation();
	CSpriteAnimation(glm::vec3 pos, float32 width, float32 height, uint32 textureId);
	~CSpriteAnimation();

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
