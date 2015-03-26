#include "Sprite.h"
#include <FreeImage.h>
#include <iostream>

CSpriteDrawAble::CSpriteDrawAble() : 
ModelMatrix( glm::mat4( 1.0f ) ),
Translate(glm::mat4(1.0f)),
Rotate(glm::mat4(1.0f)),
Scale(glm::mat4(1.0f)),
ShaderProgram(NULL) 
{
	//Generating VAO and UBO
	

	//prepare VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//prepare VBO,
	glGenBuffers(1, &VBO);

	//static uv
	glGenBuffers(1, &UV);
	
	//set uv coordinates 
	uv[0].x = 0.0f;
	uv[0].y = 0.0f;
	uv[1].x = 1.0f;
	uv[1].y = 0.0f;
	uv[2].x = 0.0f;
	uv[2].y = 1.0f;
	uv[3].x = 1.0f;
	uv[3].y = 1.0f;

	glBindBuffer(GL_ARRAY_BUFFER, UV);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec2), &uv[0], GL_STATIC_DRAW);
	
	// fill data about ... ( index data ) 
	iData[0] = 0;
	iData[1] = 1;
	iData[2] = 2;
	iData[3] = 2;
	iData[4] = 1;
	iData[5] = 3;

	
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLushort), &iData[0], GL_STATIC_DRAW);
 

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(
		0,                  // attribute 0
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, UV);
	glVertexAttribPointer(
		1,                  // attribute 1
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0); //unbind??

}

CSpriteDrawAble::~CSpriteDrawAble(){
	//delete VBOs and VAO

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &UV);
	glDeleteBuffers(1, &IBO);
	glDeleteVertexArrays(1, &VAO);

}



void CSpriteDrawAble::draw( render::RenderStates *states ) {
	
	//if (states->CurrentTexture != TextureId){
		glBindTexture( GL_TEXTURE_2D, TextureId);
		//states->CurrentTexture = TextureId;
	//}

	//if (ShaderProgram != states->CurrentShader){
		ShaderProgram->UseProgram();
		//states->CurrentShader = ShaderProgram;
	//}

	glBindVertexArray(VAO);

	Mvp = states->Cam * ModelMatrix;
	glUniformMatrix4fv( states->Uniforms.MVP, 1, GL_FALSE, &Mvp[0][0]);
	glUniform1f(states->Uniforms.Float1, ( (GLfloat)states->Time / 1000.0f));

	// Index buffer
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,      // mode
		6,    // count
		GL_UNSIGNED_SHORT,   // type
		(void*)0           // element array buffer offset
		);

	glBindVertexArray(0);
}


void CSpriteDrawAble::UpdateData(glm::vec3 *vert){
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec3), vert, GL_STATIC_DRAW);
}

//Sprite Class

CSprite::CSprite() : Pos(glm::vec3(0, 0, 0)), Height(0.0f), Width(0.0f)
{

}

CSprite::CSprite( glm::vec3 pos, GLfloat width, GLfloat height, CTexture *Texture, CShaderProgram* pShaderProgram )
{

	Pos = pos;

	Width = width;
	Height = height;
	
	//update vertices's 
	vert[0] = glm::vec3(-(Width / 2), -(Height / 2), 0.0f);
	vert[1] = glm::vec3((Width / 2), -(Height / 2), 0.0f);
	vert[2] = glm::vec3(-(Width / 2), (Height / 2), 0.0f);
	vert[3] = glm::vec3((Width / 2), (Height / 2), 0.0f);
	UpdateData(&vert[0]);


	Translate = glm::translate(pos);
	ModelMatrix = Translate * Rotate * Scale;
	
	//load texture
	TextureId = Texture->GetId();
	ShaderProgram = pShaderProgram;

}

void CSprite::SetShaderProgram(CShaderProgram* pShaderProgram){
	ShaderProgram = pShaderProgram;
}

void CSprite::SetTexture(CTexture* Texture){
	TextureId = Texture->GetId();
}


void CSprite::SetPos(glm::vec3 inPos){
	Pos = inPos;
	Translate = glm::translate(inPos);
	ModelMatrix = Translate * Rotate * Scale;
	//update VBO
	UpdateData(&vert[0]);
}	

glm::vec3 CSprite::GetPos() const {
	return Pos;
}

void CSprite::Scalef(GLfloat factor){
	Scale = glm::scale(Scale, glm::vec3(factor));
	ModelMatrix = Translate*Rotate*Scale;
}

void CSprite::Rotatef(GLfloat angle, glm::vec3 vector){
	Rotate = glm::rotate(angle, vector);
	ModelMatrix = Translate*Rotate*Scale;
}


CSprite::~CSprite(){
	glDeleteTextures(1, &TextureId);
}

