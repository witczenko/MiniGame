/*
 * shader.cpp
 *
 *  Created on: Dec 29, 2013
 *      Author: witek
 */

#include "shader.hpp"
#include <string>

// SHADERS \\

bool CShader::LoadShader( const char* ShaderTXT, GLuint shaderType)
{

	std::string ShaderCode;
	    std::ifstream ShaderStream( ShaderTXT, std::ios::in);
	    if(ShaderStream.is_open()){
	        std::string Line = "";
	        while(getline(ShaderStream, Line))
	            ShaderCode += "\n" + Line;
	        ShaderStream.close();
	    }

	shaderID = glCreateShader(shaderType);
	printf( "shader ID = %d\n", shaderID);

	const char* sProgram = ShaderCode.c_str();
	glShaderSource(shaderID, 1, &sProgram, NULL);
	glCompileShader(shaderID);

	GLint compilationError;
	glGetShaderiv( shaderID, GL_COMPILE_STATUS, &compilationError);
	if( compilationError == GL_FALSE )
	{
		printf("%s %s ;(\n", "Shader compilation problem with:", ShaderTXT);
		fprintf(stderr, "%s %s ;(\n", "Shader compilation problem with:", ShaderTXT);
		GLint blen = 0;
		GLsizei slen = 0;
		glGetShaderiv( shaderID, GL_INFO_LOG_LENGTH , &blen);
		printf( "BLEN =  %d \n", blen);
		if (blen > 1)
		{
		 GLchar* compiler_log = (GLchar*)malloc(blen);
		 glGetInfoLogARB( shaderID, blen, &slen, compiler_log);
		 printf("compiler_log: %s\n", compiler_log);
		 fprintf(stderr,"compiler_log: %s\n", compiler_log);
		 free (compiler_log);
		}
		return false;
	};
	ishaderType = shaderType;
	isLoaded = true;
	return 1;
};

bool CShader::IsLoaded()
{
	return isLoaded;
}

GLuint CShader::GetShaderID()
{
	return shaderID;
}

void CShader::DeleteShader()
{
	if( isLoaded )
		{
			glDeleteShader(shaderID);
			isLoaded = false;
		}
}

CShaderProgram::CShaderProgram()
{
	isLinked = false;
}

void CShaderProgram::CreateProgram()
{
	programID = glCreateProgram();
}

GLuint CShaderProgram::getProgramID()
{
	return programID;
}

bool CShaderProgram::AddShaderToProgram(CShader* Shader)
{
	if( !Shader->IsLoaded() ) return false;
	glAttachShader( programID, Shader->GetShaderID());
	return true;
}

bool CShaderProgram::LinkProgram()
{
	glLinkProgram(programID);
	GLint linkStatus;
	glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
	if( linkStatus == GL_FALSE )
	{
		printf("Shader linking problem\n");
		fprintf(stderr,"Shader linking problem\n");
	}
	isLinked = linkStatus;
	return isLinked;
}

void CShaderProgram::DeleteProgram()
{
	if( !isLinked ) return;
	isLinked = false;
	glDeleteProgram(programID);
}

void CShaderProgram::UseProgram()
{
	if( isLinked ) glUseProgram(programID);
}
