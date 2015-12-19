#ifndef CGAME_H
#define CGAME_H

#define FORCE_GL_3

#include "GameUtils.h"
#include "Camera.h"
#include "TextureManager.h"
#include "Scene.h"

/* SCREEN RESOLUTION BIG/SMALL SCREEN */
#if 0
#define WIDTH	( 1680 ) 
#define HEIGHT	( 1050 )
#else
#define WIDTH	( 1366 ) 
#define HEIGHT	( 768 )
#endif

#define ASPECT	(WIDTH/(float32)HEIGHT)
#define FOV		(45.0f)

#define CAM_SPEED ( 0.2f );

#define CURSOR_WIDTH	(50.0f) /* [px] */
#define CURSOR_HEIGHT   (50.0f) /* [px] */

#define FPS_LOCK	(1)
#define FPS		    (45)

//GL_Version 
#define GL_MAJOR ( 3 )
#define GL_MINOR ( 1 )

#define GAME_LOG_FILE	"game_log.txt"

#define VSLOGERR(log, message, ...) \
{\
	printf(message, ## __VA_ARGS__);\
	(log.addMessage(message, ## __VA_ARGS__)); \
};



struct StartCfg{
	int fullScreen;
	int winHeight;
	int winWidth;
	int vSync;
};

void SpawnMob(CScene &scene, CTextureManager &texMan, glm::vec3 pos, const std::string & anim_prefix);

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
	unsigned int renderLog,  debugInfo;
	std::string renderLogStr;

	/* ---- Mouse ----*/
	glm::vec3 rayDir; // <-- camera-mouse direction

	/* Mouse position on XY plane */
	glm::vec2 mouse2dWorldPosition; // <-- mouse positon on X-Y plane (z = 0.0f) 
	glm::vec2 normalizedMousePos; // <-- normalized mouse position value beetween [-1,1]
	uint32 mouse_x; 
	uint32 mouse_y; 
	CTextureManager textureMan;
	VSBasicRender shapeRender;
	CCamera Cam;
	CScene MainScene;
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

	void GetMousePos(uint32 &x, uint32 &y);
	void GetNormalizedMousePos(float &x, float &y);
	void GetMouse2dWorldPositon(float &x, float &y);
	void GetWindowSize(uint32 &width, uint32 &height);
	CScene& GetScene();
	CCamera& GetCamera();
	CTextureManager& GetTextureManager();
	VSLogLib& GetLog();
	std::string& GetRenderLog();

	static CGame & GetGameInstance(){
		static CGame Game;
		return Game;
	}
};

#endif // CGAME_H
