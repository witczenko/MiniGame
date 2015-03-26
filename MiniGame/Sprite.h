/**
\brief Header class of CSprite class
\file Sprite.h
\author Witczenko
*/

#ifndef CSPRITE_H
#define CSPRITE_H

#include "Render.h"
#include "Texture.h"

/**
 * A class... TODO: Description
*/
class CSpriteDrawAble{
public:
	CSpriteDrawAble();
	virtual ~CSpriteDrawAble();
	virtual void draw( render::RenderStates *states);

protected:	
	glm::vec2 uv[4];
	glm::mat4 ModelMatrix;
	glm::mat4 Scale;
	glm::mat4 Rotate;
	glm::mat4 Translate;
	glm::mat4 Mvp;	
	GLuint TextureId;
	CShaderProgram* ShaderProgram;

	void UpdateData(glm::vec3 *verts);

private:
	GLuint VAO;
	GLuint VBO;
	GLuint UV;
	GLuint MvpId, IGlobalTimeId, UniformTextureId;
	

	//Index Data
	GLuint IBO;
	GLshort iData[6];

};


 class CSprite : public CSpriteDrawAble
{
public:
	
	CSprite(); 
	virtual ~CSprite();

	CSprite(glm::vec3 pos, GLfloat width, GLfloat height, CTexture *Texture, CShaderProgram* pShaderProgram);
	void SetTexture(CTexture *pTexture);
	void SetShaderProgram( CShaderProgram* pShaderProgram);
	void SetPos( glm::vec3 pos);
	void Rotatef(GLfloat angle, glm::vec3 vector);
	void Scalef(GLfloat factor);
	

	//Getters
	glm::vec3 GetPos() const;
	GLfloat GetPosX();
	GLfloat GetPosY();

protected:
	glm::vec3 vert[4];
	GLfloat Width, Height;
	glm::vec3 Pos;
};

#endif // CSPRITE_H

