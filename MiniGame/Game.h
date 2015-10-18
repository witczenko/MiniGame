#ifndef CGAME_H
#define CGAME_H

#include "Types.h"
#include <GL/glew.h>
#include "SDL/SDL.h"
#include "Input.h"
#include "Camera.h"
#include <glm\glm.hpp>

#define FORCE_GL_3
#include "VSL/vslibs.h"

#include "GameUtils.h"
#include "Scene.h"
#include "GameObject.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "MapHandler.h"

#include <iostream>
#include <fstream>

/* SCREEN RESOLUTION BIG/SMALL SCREEN */
#if 0
#define WIDTH	( 1680 ) 
#define HEIGHT	( 1050 )
#else
#define WIDTH	( 1366 ) 
#define HEIGHT	( 768 )
#endif

#define ASPECT	(WIDTH/(float32)HEIGHT)
#define FOV		(60.0f)

#define CAM_SPEED ( 0.2f );

#define CURSOR_WIDTH	(50.0f) /* [px] */
#define CURSOR_HEIGHT   (50.0f) /* [px] */

#define FPS_LOCK	(1)
#define FPS		    (45)

//GL_Version 
#define GL_MAJOR ( 3 )
#define GL_MINOR ( 1 )

struct StartCfg{
	int fullScreen;
	int winHeight;
	int winWidth;
	int vSync;
};


class CGame : CInputInterface {
private:	
	VSLogLib log;
	VSMathLib & vsml;
	VSShaderLib basicShader, lineShader;
	VSFontLib basicFont;
	unsigned int aSentence, debugInfo;

	glm::vec3 rayDir;

	VSBasicRender shapeRender;
	CCamera *Cam;
	CScene *MainScene;
	CMapHandler *Map1;

	/* Mouse position on XY plane */
	glm::vec2 mouse2DPosition;
	glm::vec2 normalizedMousePos;

	bool lockCam;

	StartCfg startCfg;
	SDL_Window* Win;
	SDL_GLContext MainGlContext;
	uint32 GlobalTime;

	//SDL events
	SDL_Event event;

	//Delta Time
	uint32 dt;
	bool GameRunning;


	bool Init();
	void InitVS();
	void SetupShaders();

	void Update(uint32 dt);
	void Draw(uint32 dt);
	void CalculateMousePos(const MouseArgs *Args);
	void NormalizeMousePos(uint32 screenWidth, uint32 screenHeight, uint32 inX, uint32 inY, float32 &outX, float32 &outY);
	void ParseArgs(int argc, char* args[]);
	void LoadConfig(const char* filename);
	//void LoadGameMap(const char* filename);

	void DrawAxes(void); 
	
protected:
	void OnKeyDown(const SDL_Keycode *Key);
	void OnMouseMove(const MouseArgs *Args);
	void OnMouseButtonDown(const MouseArgs *Args);
	void OnMouseButtonUp(const MouseArgs *Args);
	void OnMouseWheelBackward();
	void OnMouseWheelForward();
	void OnWindowExit();

public:
	CGame(int argc, char* args[]);
	bool Run();
	virtual ~CGame();
};

#endif // CGAME_H
