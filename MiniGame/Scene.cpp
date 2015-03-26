#include "Scene.h"


CScene::CScene(uint32 width, uint32 height):
cursor(NULL),
winHeight(height),
winWidth(width)
{
	//Load default ShaderProgram 
	States.CurrentShader = render::GetDefaultShaderProgram();

	States.CurrentShader->UseProgram();

	glBindAttribLocation(States.CurrentShader->getProgramID(), 0, "vertexPosition");
	glBindAttribLocation(States.CurrentShader->getProgramID(), 1, "uvData");

	//Uniforms
	Uniforms.Float1 = glGetUniformLocation(States.CurrentShader->getProgramID(), "iGlobalTime");
	Uniforms.MVP = glGetUniformLocation(States.CurrentShader->getProgramID(), "MVP");
	Uniforms.TexSampler = glGetUniformLocation(States.CurrentShader->getProgramID(), "textureSampler");

	States.Uniforms = Uniforms;
	orthoMatrix = glm::ortho(0.f, (float)width, 0.f, (float)height, -1.f, 10.f);

	glUniform1i(Uniforms.TexSampler, /*GL_TEXTURE*/0);

}

CScene::~CScene(){
	
	render::GetDefaultShaderProgram()->DeleteProgram();
	for (uint32 i = 0; i < Sprites.size(); ++i){
		delete Sprites[i];
	}
	delete cursor;

}

void CScene::DrawSprite ( CSpriteDrawAble* Sprite ){
	Sprite->draw(&States);
}

void CScene::AddToScene(CSpriteDrawAble *Sprite){
	Sprites.push_back(Sprite);
}

void CScene::Draw(CCamera *Cam){
	
	States.DeltaTime = 0;
	States.Cam = Cam->GetProjection() * Cam->GetView();
	States.Time = SDL_GetTicks();

	for (uint32 i = 0; i < Sprites.size(); ++i){
		Sprites[i]->draw(&States);
	}

	/* Draw cursor */

	
	if (cursor){
	glDisable(GL_DEPTH_TEST);
		//States.Cam = Cam->GetProjection();
	States.Cam = orthoMatrix;
		cursor->draw(&States);
	glEnable(GL_DEPTH_TEST);
	}
	
}

void CScene::SetCursor(CSpriteDrawAble *cursor){
	this->cursor = cursor;
}
