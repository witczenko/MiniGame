#include "Sprite.h"

//Sprite Class
CSprite::CSprite(glm::vec3 pos, float32 width, float32 height, uint32 textureId) : 
GameObject(pos),
width(width),
height(height),
texId(textureId),
angleZ(0.0f)
{
}

CSprite::CSprite():
GameObject(glm::vec3(0.0f, 0.0f, 0.0f)),
width(1.0),
height(1.0),
texId(0),
angleZ(0.0f)
{
}

CSprite::~CSprite(){
	
}

void CSprite::AssingTexture(unsigned int textureId)
{
	texId = textureId;
}

uint32 CSprite::GetTextureId() const{
	return texId;
}

float CSprite::GetWidth() const{
	return width;
}

float CSprite::GetHeight() const{
	return height;
}

float CSprite::GetAngleZ() const{
	return angleZ;
}

void CSprite::SetAngleZ(float32 angle){
	angleZ = angle;
}




/* SPRITE RENDERER*/

CSpriteRenderer::CSpriteRenderer() :vsml(*VSMathLib::getInstance())
{
	
}

CSpriteRenderer::~CSpriteRenderer()
{
	for (auto sprite : spriteCollection)
	{
		if (sprite)
			delete sprite;
	}

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &UV);
	glDeleteVertexArrays(1, &VAO);
}

void CSpriteRenderer::Init()
{
	//1 triangle
	vert[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
	vert[1] = glm::vec3(-1.0f, 1.0f, 0.0f);
	vert[2] = glm::vec3(1.0f, 1.0f, 0.0f);
	//2 triangle
	vert[3] = glm::vec3(-1.0f, -1.0f, 0.0f);
	vert[4] = glm::vec3(1.0f, 1.0f, 0.0f);
	vert[5] = glm::vec3(1.0f, -1.0f, 0.0f);

	//uv for 1 tri
	uv[0].x = 0.0f;
	uv[0].y = 0.0f;
	uv[1].x = 0.0f;
	uv[1].y = 1.0f;
	uv[2].x = 1.0f;
	uv[2].y = 1.0f;

	//uv for 2 tri
	uv[3].x = 0.0f;
	uv[3].y = 0.0f;
	uv[4].x = 1.0f;
	uv[4].y = 1.0f;
	uv[5].x = 1.0f;
	uv[5].y = 0.0f;

	GenBuffers();
}

void CSpriteRenderer::Render()
{
	glBindVertexArray(VAO);
	// Bind texure, send matrices to GL...
	for (auto sprite : spriteCollection)
	{
		vsml.pushMatrix(VSMathLib::MODEL);
		vsml.translate(sprite->GetPos().x, sprite->GetPos().y, sprite->GetPos().z);
		vsml.rotate(sprite->GetAngleZ(), 0.0, 0.0, 1.0);
		vsml.scale(sprite->GetWidth(), sprite->GetHeight(), 0.0f);

		vsml.matricesToGL();
		vsml.popMatrix(VSMathLib::MODEL);

		glBindTexture(GL_TEXTURE_2D, sprite->GetTextureId());
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	glBindVertexArray(0);
}

void CSpriteRenderer::AddSprite(CSprite* sprite){
	spriteCollection.push_back(sprite);
}

void CSpriteRenderer::GenBuffers(){
	//prepare VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//prepare VBO,
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &UV);

	//UV
	glBindBuffer(GL_ARRAY_BUFFER, UV);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), &uv[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(VSShaderLib::TEXTURE_COORD_ATTRIB);
	glVertexAttribPointer(VSShaderLib::TEXTURE_COORD_ATTRIB, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//VERTICES 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), &vert[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(VSShaderLib::VERTEX_COORD_ATTRIB);
	glVertexAttribPointer(VSShaderLib::VERTEX_COORD_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);


	glBindVertexArray(0); //unbind??

}
