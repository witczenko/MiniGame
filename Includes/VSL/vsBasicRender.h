#ifndef __VSBasicRender__
#define __VSBasicRender__

#include "vsMathLib.h"

class VSBasicRender
{
private:
	GLuint vao, vbo;
	VSMathLib & vsml;
	
	bool initialized;
public:
	VSBasicRender();
	~VSBasicRender();

	// Draws line strip
	// vert - pointer to vertex data
	// num - number of vertices
	void DrawLine(float *vert, int num);
	void SetColor(float *color);
	void Init();
};

#endif

