/**
\brief Header class of CSprite class
\file Sprite.h
\author Witczenko
*/

#ifndef CSPRITE_H
#define CSPRITE_H

#include <GL/glew.h>
#include "GameObject.h"
#include "VSL/vslibs.h"


class CSprite :public GameObject 
{
public:
	CSprite(glm::vec3 pos, float32 width, float32 height, uint32 textureId);
	CSprite();

	virtual ~CSprite();
	
	void AssingTexture(unsigned int textureId);
	uint32 GetTextureId() const;
	float32 GetWidth() const;
	float32 GetHeight() const;
	float32 GetAngleZ() const;
	void SetAngleZ(float32 angle);
	void SetWidth(float32 width);
	void SetHeight(float32 height);

private:
	GLfloat width, height;
	GLfloat angleZ;
	uint32 texId;
};



 class CSpriteRenderer
 {
 public:
	 CSpriteRenderer();
	 ~CSpriteRenderer();
	 void Render(std::vector<CSprite*> & spriteCollection);
	 void Init();

 private:
	 VSMathLib &vsml;

	 void GenBuffers();
	 void OrderByZAxis(std::vector<CSprite*> & spriteCollection);

	 GLuint VAO;
	 GLuint VBO;
	 GLuint UV;
	 glm::vec3 vert[6];
	 glm::vec2 uv[6];
	 GLuint textID;
 };



#endif // CSPRITE_H

