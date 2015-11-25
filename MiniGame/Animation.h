#ifndef ANIMATION_H
#define ANIMATION_H
#include "Sprite.h"

struct AnimTexData{
	uint32 start_tex;   /*<-  id of first animation texture */
	uint32 count;		/*<- ammount of animtion frames */
};

/* Sprite animation */
class CSpriteAnimation : public CSprite
{
public:
	CSpriteAnimation();
	CSpriteAnimation(glm::vec3 pos, float32 width, float32 height, uint32 textureId);
	~CSpriteAnimation();

	uint32 GetFrame() const; //return texture ID 
	void SetAnimation(AnimTexData anim_data);
	void SetFPS(uint32 fps);
	void Update(uint32 dt);

private:
	AnimTexData anim_data;
	uint32 current_frame;
	uint32 anim_time;
	uint32 frame_time;
	bool is_loaded;

};

#endif
