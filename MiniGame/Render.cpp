#include "Render.h"
#include <iostream>

CShaderProgram DefaultShader;

void render::Init(){
	CShader fShader, vShader;

	vShader.LoadShader(DEFAULT_VS, GL_VERTEX_SHADER);
	fShader.LoadShader(DEFAULT_FS, GL_FRAGMENT_SHADER);

	if (vShader.IsLoaded() && fShader.IsLoaded()){

		DefaultShader.CreateProgram();
		DefaultShader.AddShaderToProgram(&vShader);
		DefaultShader.AddShaderToProgram(&fShader);
		DefaultShader.LinkProgram();

		vShader.DeleteShader();
		fShader.DeleteShader();

	}
	else{
		//error
		if (!vShader.IsLoaded()) std::cerr << "Can't load vertex shader:" << DEFAULT_VS << std::endl;
		if (!fShader.IsLoaded()) std::cerr << "Can't load fragment shader:" << DEFAULT_FS << std::endl;
	}
}

CShaderProgram *render::GetDefaultShaderProgram(){
	return &DefaultShader;
}

CShaderProgram *render::LoadShader(const char* Vshader, const char* Fshader){
	//Create new CShaderProgram
	CShaderProgram *Program = new CShaderProgram;
	
	CShader fShader, vShader;
	vShader.LoadShader(DEFAULT_VS, GL_VERTEX_SHADER);
	fShader.LoadShader(DEFAULT_FS, GL_FRAGMENT_SHADER);

	if (vShader.IsLoaded() && fShader.IsLoaded()){

		Program->CreateProgram();
		Program->AddShaderToProgram(&vShader);
		Program->AddShaderToProgram(&fShader);
		Program->LinkProgram();

		vShader.DeleteShader();
		fShader.DeleteShader();
		return Program;
	}
	else{
		//error
		if (!vShader.IsLoaded()) std::cerr << "Can't load vertex shader:" << DEFAULT_VS << std::endl;
		if (!fShader.IsLoaded()) std::cerr << "Can't load fragment shader:" << DEFAULT_FS << std::endl;
		return NULL;
	}
}

void render::SetUniforms(CShaderProgram* Program){
	/*TODO*/
}