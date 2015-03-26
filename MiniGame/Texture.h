#ifndef TEXTURE_H
#define TEXTURE_H
#include <GL\glew.h>

class CTexture
{
public:
	CTexture();
	CTexture(const char* texPath);
	bool LoadTexture(const char* texPath);
	GLuint GetId();
	virtual ~CTexture();
private:
	bool Load(const char* texPath);
	bool LoadTexture1d(const char* texPath);
	GLuint TextureId;
};

#endif // TEXTURE_H

