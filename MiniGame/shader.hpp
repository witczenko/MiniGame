/*
 * shader.hpp
 *
 *  Created on: Dec 29, 2013
 *      Author: witek
 */

#ifndef SHADER_HPP_
#define SHADER_HPP_

#include <GL/glew.h>
#include <stdlib.h>
#include <vector>
#include <fstream>


class CShader
{
public:
	bool LoadShader( const char* ShaderTXT, GLuint shaderType );
	bool IsLoaded();
	GLuint GetShaderID();
	void DeleteShader();
private:
	GLuint shaderID;
	GLuint isLoaded;
	GLuint ishaderType;
};

class CShaderProgram
{
public:
	void CreateProgram();
	void DeleteProgram();
	bool AddShaderToProgram(CShader* shShader);
	bool LinkProgram();
	void UseProgram();
	GLuint getProgramID();
	CShaderProgram();
private:
	GLuint programID;;
	bool isLinked;
};

#endif /* SHADER_HPP_ */
