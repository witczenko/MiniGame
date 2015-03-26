#ifndef RENDER_H
#define RENDER_H


#define GLM_FORCE_RADIANS

#include <glm\glm.hpp>
#include <glm\gtx\matrix_operation.hpp>
#include "glm\gtx\transform.hpp"
#include <GL/glew.h>
#include "shader.hpp"
#include "Types.h"
#include <vector>

#define DEFAULT_VS  "shaders/Vshader.vs"
#define DEFAULT_FS  "shaders/Fshader.fs"


namespace render{
	/** A structure to represent shader Uniforms  */
	struct ShaderUniforms{
		GLuint MVP = 0;/**< MVP matrix, Model*View*Projection matrix */
		GLuint TexSampler;/**< Texture sampler*/
		GLuint Float1 = 0;/** Some variables e.g. global time */
		GLuint Float2 = 0;
		GLuint Int1 = 0;
	};

	struct RenderStates
	{
		CShaderProgram *CurrentShader;
		glm::mat4 Cam;
		GLuint CurrentTexture;
		uint32 DeltaTime;
		uint32 Time;
		ShaderUniforms Uniforms;
	};

	void Init();
	CShaderProgram * GetDefaultShaderProgram();
	CShaderProgram * LoadShader(const char* VShader, const char* FShader);
	void SetUniforms(CShaderProgram* Program);	
}
#endif //RENDER_H