/**
\brief nag³ówek klasy CScene
\file Scene.h
\author Witczenko 
*/


#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include "Sprite.h"
#include "Camera.h"
#include "SDL.h"

/**
Field of view settings 
*/


class CScene
{
public:
	CScene(uint32 height, uint32 width);
	
	void SetCursor(CSpriteDrawAble *cursor);
	void AddToScene( CSpriteDrawAble* Sprite );

	/**
	 * \brief Draw directly our sprite. \n
	 * Don't delete pointer to your sprite, we'll do it for you 
	 * \param Sprite pointer to Sprite object which we want to draw  
	 * \return nothing
	 */
	void DrawSprite( CSpriteDrawAble* Sprite );

	/** 
	 *	\brief Draw whole scene
	 *	\param dt delta time 
	 *	\return nothing
	 */
	void Draw(CCamera *cam);

	~CScene();


private:
	render::RenderStates States;
	render::ShaderUniforms Uniforms;
	std::vector<CSpriteDrawAble*> Sprites;

	uint32 winWidth, winHeight;
	CSpriteDrawAble *cursor;

	glm::mat4x4 orthoMatrix;
};

#endif // SCENE.H