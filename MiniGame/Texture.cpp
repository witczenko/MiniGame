#include "Texture.h"
#include <FreeImage.h>
#include <iostream>

CTexture::CTexture() : TextureId(0)
{
}

CTexture::CTexture(const char* texPath){
	Load(texPath);
}

bool CTexture::LoadTexture(const char* texPath){
	if (Load(texPath)) return true;
	else return false;
}

GLuint CTexture::GetId(){
	return TextureId;
}

bool CTexture::Load(const char* texPath){
	//if we already load texture, you have to delete previous...
	if (TextureId != NULL) glDeleteTextures(1, &TextureId);


	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(texPath, 0);
	FIBITMAP* image = FreeImage_Load(format, texPath);

	if (format == FIF_UNKNOWN){
		std::cout << "unknown texture format: file " << texPath << std::endl;
		return false;
	};


	FIBITMAP* temp = image;
	image = FreeImage_ConvertTo32Bits(image);
	FreeImage_Unload(temp);

	int w = FreeImage_GetWidth(image);
	int h = FreeImage_GetHeight(image);

	char* bits = (char*)FreeImage_GetBits(image);


	// OpenGL stuff

	/* TODO: Texture settings */
	glGenTextures(1, &TextureId);
	glBindTexture(GL_TEXTURE_2D, TextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)bits);

	/* Generate Mipmap */
	glGenerateMipmap(GL_TEXTURE);

	//glGenerateTextureMipmapEXT(TextureId);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	GLfloat fLargest;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);

	GLenum Error = glGetError();
	if (Error){
		std::cerr << "There was an error loading the texture" << std::endl;
		return false;
	}

	return true;
}

CTexture::~CTexture()
{
	glDeleteTextures(1, &TextureId);
}
