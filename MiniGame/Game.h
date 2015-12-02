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
#include "Player.h"
#include "Mob.h"

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
	StartCfg startCfg; 
	VSLogLib log;
	VSMathLib & vsml;
	SDL_Window* Win;
	SDL_GLContext MainGlContext;
	//Fonts
	VSShaderLib basicShader, lineShader;
	VSFontLib basicFont;
	unsigned int aSentence, debugInfo;

	/* ---- Mouse ----*/
	glm::vec3 rayDir; // <-- camera-mouse direction

	/* Mouse position on XY plane */
	glm::vec2 mouse2dWorldPosition; // <-- mouse positon on X-Y plane (z = 0.0f) 
	glm::vec2 normalizedMousePos; // <-- normalized mouse position value beetween [-1,1]
	uint32 mouse_x; 
	uint32 mouse_y; 

	VSBasicRender shapeRender;
	CCamera *Cam;
	CScene *MainScene;
	CMapHandler *Map1;
	//CPlayer *Player1;
	//CMob *Mob1,*Mob2;
	bool lockCam;

	//SDL events
	SDL_Event event;

	/* ---- TIME ---*/
	uint32 dt; 
	uint32 GlobalTime;
	bool GameRunning;

	/*  --- FUNCTIONS --- */
	CGame();

	bool Init();
	void InitVS();
	void SetupShaders();

	void Update(uint32 dt);
	void Draw(uint32 dt);
	void CalculateMousePos(const MouseArgs *Args);	
	void ParseArgs(int argc, char* args[]);
	void LoadConfig(const char* filename);
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
	bool Run();
	virtual ~CGame();
	
	CCamera *GetCamera();
	void GetWindowSize(uint32 &width, uint32 &height);

	/* TODO */
	void GetMousePos(uint32 &x, uint32 &y);
	void GetNormalizedMousePos(float &x, float &y);
	void GetMouse2dWorldPositon(float &x, float &y);

	static CGame & GetGameIntance(){
		static CGame Game;
		return Game;
	}
};

#endif // CGAME_H
