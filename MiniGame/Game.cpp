#include "Game.h"
#include "GameUtils.h"
#include "Animation.h"
#include "Types.h"
#include <GL/glew.h>
#include "SDL/SDL.h"
#include "Input.h"
#include "Camera.h"
#include "Scene.h"
#include "GameObject.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "Player.h"
#include "Mob.h"
#include "Asteroid.h"

#define AXES_LENGTH (10e5)

float red[4] = { 1.0, 0.0, 0.0, 1.0 };
float green[4] = { 0.0, 1.0, 0.0, 1.0 };
float blue[4] = { 0.0, 0.0, 1.0, 1.0 };


CGame::CGame() :
Win(0),
MainGlContext(NULL),
GlobalTime(0),
GameRunning(true),
mouse2dWorldPosition(0.0f, 0.0f),
lockCam(false),
Cam(CCamera(FOV, ASPECT, 0.1f, 200.0f)),
vsml(*VSMathLib::getInstance())
{
	/* Prepare initial config (basic settings) */
	startCfg.fullScreen = false;
	startCfg.winHeight = HEIGHT;
	startCfg.winWidth = WIDTH;
	startCfg.vSync = true;

	LoadConfig("config.xml");
	//ParseArgs(argc, args);
}

void SpawnMob(CScene &scene, CTextureManager &texMan, glm::vec3 pos, const std::string & anim_prefix){
	CMob *Mob = new CMob;
	CSpriteAnimation *spriteAnim = new CSpriteAnimation;
	AnimTexData anim_data;

	Mob->SetPos(pos);
	Mob->SetCollideFlag(true);

	if (texMan.GetAnimation(anim_prefix, anim_data)){
		spriteAnim->SetAnimation(anim_data);
		spriteAnim->SetPos(pos);
		spriteAnim->SetFPS(24);
		spriteAnim->SetHeight(0.3f);
		spriteAnim->SetWidth(0.3f);
		Mob->sprite_anim = spriteAnim;
		scene.AddObject(Mob, GameObject::OBJECT_TYPE::MOB);
	}
	else{
		delete Mob;
		delete spriteAnim;
	}

	
}

void SpawnPlayer(CScene &scene, CTextureManager &texMan, glm::vec3 pos, const std::string & anim_prefix, const std::string & bullet_anim_prefix, const std::string & rocket_anim_prefix){
	CPlayer *Player = new CPlayer;
	CSpriteAnimation *spriteAnim = new CSpriteAnimation;
	AnimTexData anim_data;

	Player->SetPos(pos);
	Player->SetCollideFlag(true);

	if (texMan.GetAnimation(anim_prefix, anim_data)){
		spriteAnim->SetAnimation(anim_data);
		spriteAnim->SetPos(pos);
		spriteAnim->SetFPS(24);
		spriteAnim->SetHeight(0.4f);
		spriteAnim->SetWidth(0.4f);

		Player->sprite_anim = spriteAnim;
		scene.AddObject(Player, GameObject::OBJECT_TYPE::PLAYER);

		spriteAnim = NULL;
		spriteAnim = new CSpriteAnimation;

		if (texMan.GetAnimation(bullet_anim_prefix, anim_data))
		{
			spriteAnim->SetAnimation(anim_data);
			spriteAnim->SetPos(pos);
			spriteAnim->SetFPS(24);
			spriteAnim->SetHeight(0.1f);
			spriteAnim->SetWidth(0.1f);

			Player->primary.sprite_anim = spriteAnim;
		}
		else
		{
			delete spriteAnim;
			spriteAnim = NULL;
		}
		
		spriteAnim = NULL;
		spriteAnim = new CSpriteAnimation;

		if (texMan.GetAnimation(rocket_anim_prefix, anim_data))
		{
			spriteAnim->SetAnimation(anim_data);
			spriteAnim->SetPos(pos);
			spriteAnim->SetFPS(24);
			spriteAnim->SetHeight(0.2f);
			spriteAnim->SetWidth(0.2f);

			Player->secondary.sprite_anim = spriteAnim;
		}
		else
		{
			delete spriteAnim;
			spriteAnim = NULL;
		}
	}
	else{
		delete Player;
		delete spriteAnim;
		spriteAnim = NULL;
	}
}

CGame::~CGame()
{
	log.dumpToFile(GAME_LOG_FILE);
	SDL_GL_DeleteContext(MainGlContext);
	SDL_DestroyWindow(Win);
	SDL_Quit();
}

void CGame::ParseArgs(int argc, char* args[]){
	for (int i = 0; i < argc; i++)
	{
		/*TODO: PARSE COMMAND LINE */
		//std::cout << args[i];
		/*
		if (0 == strcmp("w", args[1])){
			// run windowed 
			startCfg.winCfg = CFG_WINDOWED;
		}

		
		if (i == 2){
			startCfg.winWidth = atoi(args[i]);
		}

		if (i == 3){
			startCfg.winHeight = atoi(args[i]);
		}
		*/

	}		
}

void CGame::LoadConfig(const char* filename){

	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError err = doc.LoadFile(filename);

	if (err == tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED) {
		VSLOG(log, "Problem reading games config file: %s", filename);
		return;
	}

	tinyxml2::XMLHandle hDoc(&doc);
	tinyxml2::XMLHandle hRoot(0);
	tinyxml2::XMLElement *pElem;

	pElem = hDoc.FirstChildElement().ToElement();
	if (0 == pElem)
		return;

	hRoot = tinyxml2::XMLHandle(pElem);
	
	/// Window
	pElem = hRoot.FirstChildElement("Window").ToElement();
	pElem->QueryIntAttribute("Width", &startCfg.winWidth);
	pElem->QueryIntAttribute("Height", &startCfg.winHeight);
	pElem->QueryIntAttribute("FullScreen", &startCfg.fullScreen);
	
	/// Graphics
	pElem = hRoot.FirstChildElement("Graphics").ToElement();
	pElem->QueryIntAttribute("Vsync", &startCfg.vSync);

}

bool CGame::Init(){	
	VSLOGERR(log, "---- Start logging ----\nInit SDL:\n");	
	srand((uint32)time((NULL)));
	//INIT SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
		VSLOGERR(log, SDL_GetError());		
		log.dumpToFile(GAME_LOG_FILE);
		return false;
	}

	//SDL_ShowCursor(SDL_DISABLE);
	//SET OPENGL CONTEXT TO 3.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_MAJOR);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_MINOR);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	switch (startCfg.fullScreen){
	case 1: Win = SDL_CreateWindow("MiniGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
													startCfg.winWidth, startCfg.winHeight, 
													SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
	break;

	case 0:  //Win = SDL_CreateWindow("MiniGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, startCfg.winWidth, startCfg.winHeight, SDL_WINDOW_OPENGL );
						  Win = SDL_CreateWindow("SOBA - dev ", 0, 100, 
												  startCfg.winWidth, startCfg.winHeight, SDL_WINDOW_OPENGL);
	break;
	}
	
	if (Win == 0){
		VSLOGERR(log, SDL_GetError());
		log.dumpToFile(GAME_LOG_FILE);
		return false;
	}

	MainGlContext = SDL_GL_CreateContext(Win);

	if (startCfg.vSync){
		if (SDL_GL_SetSwapInterval(1) < 0)
			VSLOGERR(log, "\tWarning: Unable to set VSync! SDL Error: %s\n", SDL_GetError())
	}

	/* GLEW STUFF */
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();

	//Check OpenGl extensions	
	VSLOGERR(log, "Init OpenGL:\n");
	if (glewError == GLEW_OK){
		if (!glewIsSupported("GL_ARB_vertex_buffer_object"))
		{
			VSLOGERR(log, "\tGL_ARB_vertex_buffer_object is not supported.");
			log.dumpToFile(GAME_LOG_FILE);	
		}	

		if (!glewIsSupported("GL_EXT_direct_state_access")){
			VSLOGERR(log, "\tGL_EXT_direct_state_access is not supported.\n");
		}

		if (!glewIsSupported("GL_ARB_uniform_buffer_object")){
			VSLOGERR(log, "\tGL_ARB_uniform_buffer_object is not supported.\n");
		}

		if (!glewIsSupported("GL_VERSION_3_1"))
		{
			VSLOGERR(log, "\tOpenGL 3.1 is not supported.\n");
		}

		//GL SETTINGS 
		// Enable depth test	

		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		glEnable(GL_MULTISAMPLE);
		//glClearColor(.3f, .3f, .3f, 1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//wireframe mode
		//glPolygonMode(GL_FRONT, GL_LINE);
		//glPolygonMode(GL_BACK, GL_LINE);
		log.dumpToFile(GAME_LOG_FILE);
	}
	else{	
		VSLOGERR(log, (const char*)glewGetErrorString(glewError));
		log.dumpToFile(GAME_LOG_FILE);
		return false;
	}
	return true;
}


void CGame::InitVS(){
	vsml.loadIdentity(VSMathLib::VIEW);
	vsml.loadIdentity(VSMathLib::MODEL);
	vsml.setUniformName(VSMathLib::PROJ_VIEW_MODEL, "projViewModelMatrix");
	vsml.setUniformName(VSMathLib::NORMAL, "normalMatrix");

	bool loaded = basicFont.load("fonts/couriernew10");
	if (loaded == false){
		VSLOGERR(log, "Cant load fonts/couriernew10 font...");
	}

	basicFont.setFixedFont(true);
	basicFont.setColor(1.0f, 0.5f, 0.25f, 1.0f);
	debugInfo = basicFont.genSentence();
	renderLog = basicFont.genSentence();

	shapeRender.Init();
}

void CGame::SetupShaders(){
	// Shader for fonts and models
	basicShader.init();
	basicShader.loadShader(VSShaderLib::VERTEX_SHADER, "gfx/shaders/dirlightdiffambpix.vert");
	basicShader.loadShader(VSShaderLib::FRAGMENT_SHADER, "gfx/shaders/dirlightdiffambpix.frag");

	// set semantics for the shader variables
	basicShader.setProgramOutput(0, "outputF");
	basicShader.setVertexAttribName(VSShaderLib::VERTEX_COORD_ATTRIB, "position");
	basicShader.setVertexAttribName(VSShaderLib::TEXTURE_COORD_ATTRIB, "texCoord");
	basicShader.setVertexAttribName(VSShaderLib::NORMAL_ATTRIB, "normal");
	basicShader.prepareProgram();

	basicShader.useProgram();
	VSLOGERR(log, "Load shaders:\n\t%s\n\n", basicShader.getAllInfoLogs().c_str());
	
	basicShader.setUniform("texUnit", 0);
}


bool CGame::Run(){
	//VSGLInfoLib::getGeneralInfo();
	uint32 OldTime = 0;
	uint32 CurrentTime = 0;

	/* Init Game */
	if (Init() == false){
		return false;
	}

	InitVS();
	SetupShaders();

	vsml.loadIdentity(VSMathLib::PROJECTION);
	vsml.perspective(53.13f, ASPECT, 0.1f, 10000.0f);

	MainScene.Init();
	textureMan.Init(); // <-- Here all textures and animations are loaded
	CAsteroidManager asterMan;
	asterMan.Init();


	uint32 TEXTURE_2 = textureMan.GetTexture("gfx/skybox/skybox1/1.png");
	CSprite* bg = new CSprite(glm::vec3(0.0f, 0.0f, -1.0f), 1.5f * 5, 1.0f * 5, TEXTURE_2);
	bg->SetCollisionRad(10.0f);

	//ADD BACKGROUND 
	MainScene.AddObject(bg, GameObject::SPRITE);
	
	// CREATE MOBS AND PLAYER
	SpawnMob(MainScene, textureMan, glm::vec3(-1.0f, 0.0f, 0.1f), "gfx/Spaceship_art_pack/Red/Enemy_animation/");
	SpawnPlayer(MainScene, textureMan, glm::vec3(0.0f, 0.0f, 0.0f), "gfx/Spaceship_art_pack/Blue/Animation/","gfx/Spaceship_art_pack/Blue/Bullet/","gfx/Spaceship_art_pack/Blue/Spacebombs/");
	//SpawnMob(MainScene, textureMan, glm::vec3(-1.0f, -1.0f, -0.1f), "gfx/Spaceship_art_pack/Blue/Enemy_animation/");

	char fps[64] = "";
	uint32 acc = 0;\

	VSLOGERR(log, "\nGame running:\n");
	/* Main Loop */
	while (GameRunning){
		GlobalTime = SDL_GetTicks();

		//Time stuff
		OldTime = CurrentTime;
		CurrentTime = SDL_GetTicks();
		dt = (CurrentTime - OldTime);

		//update fps every 1000ms - PRIMITIVE!
		acc += dt;
		if (acc > 200)
		{
			acc = 0;
			if (startCfg.vSync)
				sprintf(fps, "FPS %f \nVSYNC ON", (1000.0f / dt));
			else
				sprintf(fps, "FPS %f \nVSYNC OFF", (1000.0f / dt));
				basicFont.prepareSentence(debugInfo, fps);
		}

		//Handle input
		Update(dt);

		//Draw 
		Draw(dt);

		/* //Do poprawki - regulacja FPS 
		if (FPS_LOCK){
			int delay = (1000 / FPS) - dt;
			if (delay > 0)
				SDL_Delay(delay);
		}
		*/
		SDL_Delay(1);
	}


	return true;
}

void CGame::Update(uint32 dt){
	char obj_str[128];
	sprintf(obj_str, "Object counter: %d\nCamera position: %f %f %f\n", GameObject::GetObjectCount(), Cam.GetPosition().x, Cam.GetPosition().y, Cam.GetPosition().z);

	renderLogStr = "**** Debug info ****\n";
	renderLogStr += obj_str;

	basicShader.setUniform("time", GlobalTime/1000.0f);
	GlobalTime += dt;
	CInputManager::GetInputManager().Update(dt);
	MainScene.Update(dt);

}

void CGame::Draw(uint32 dt){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	basicShader.useProgram();

	

	static int time = 0;
	time += dt;

	vsml.loadIdentity(VSMathLib::VIEW);
	vsml.loadIdentity(VSMathLib::MODEL);

	// set camera
	vsml.lookAt(Cam.GetPosition().x, Cam.GetPosition().y, Cam.GetPosition().z, 
				  Cam.GetTarget().x, Cam.GetTarget().y, Cam.GetTarget().z, 0, 1, 0);

	
	vsml.pushMatrix(VSMathLib::MODEL);

	basicShader.setUniform("texCount", 1);
	MainScene.Draw();

	vsml.popMatrix(VSMathLib::MODEL);

	DrawAxes();
	basicFont.prepareSentence(renderLog, renderLogStr);
	basicFont.renderSentence(10, 10, debugInfo);	
	basicFont.renderSentence(10, 100, renderLog);

	SDL_GL_SwapWindow(Win);
}



void CGame::OnKeyDown(const SDL_Keycode *Key){
	if (*Key == SDLK_ESCAPE){
		GameRunning = false;
	}else
	if (*Key == SDLK_1) {
		Cam.SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
		Cam.SetTarget(glm::vec3(0.0f, 0.0f, 0.0f));
	}else
	if (*Key == SDLK_2) {
		lockCam = true;
	}else
	if (*Key == SDLK_3) {
		lockCam = false;
	}else
	if (*Key == SDLK_4) {
		//boxEmmiter = true;
	}else
	if (*Key == SDLK_5) {
	//	boxEmmiter = false;
	}else
	if (*Key == SDLK_m){
		//modelRot.y += 10.0f;
	}
	else
	if (*Key == SDLK_n){
		//modelRot.y -= 10.0f;
	}else
	if (*Key == SDLK_b){
		//modelRot.p += 10.0f;
	}
	else if (*Key == SDLK_v){
		//modelRot.p -= 10.0f;
	}
	
}

void CGame::OnWindowExit(){
	GameRunning = false;
}


void CGame::OnMouseMove(const MouseArgs *Args){
	CalculateMousePos(Args);

	glm::vec2 mousePos = glm::vec2(Args->x, Args->y);
	

	if (Args->button == MLeft){
		if (!lockCam){
			glm::vec3 CamPos = Cam.GetPosition();
			glm::vec3 CamTarget = Cam.GetTarget();

			CamPos.x += (float32)(Args->dx / 200.0f)*CAM_SPEED;
			CamPos.y -= (float32)(Args->dy / 200.0f)*CAM_SPEED;


			CamTarget.x += (float32)(Args->dx / 100.0f)*CAM_SPEED;
			CamTarget.y -= (float32)(Args->dy / 59.0f)*CAM_SPEED;

			Cam.SetPosition(CamPos);
			Cam.SetTarget(CamTarget);
		}
	}

	if (Args->button == MRight){

	}


};

void CGame::OnMouseButtonDown(const MouseArgs *Args){
	if (Args->button == MRight){
		
	}

	if (Args->button == MLeft){
	
	}
}

void CGame::OnMouseButtonUp(const MouseArgs *Args){
	if (Args->button == MLeft){
	}
}

void CGame::OnMouseWheelBackward(){
	glm::vec3 CamPos = Cam.GetPosition();
	CamPos.z += 0.6f;
	Cam.SetPosition(CamPos);
}

void CGame::OnMouseWheelForward(){
	glm::vec3 CamPos = Cam.GetPosition();
	if ((CamPos.z - 0.6) > 0.1)
	{
		CamPos.z -= 0.6f;
		Cam.SetPosition(CamPos);
	}
}

void CGame::CalculateMousePos(const MouseArgs *Args){
	/* normalize mouse position  */
	mouse_x = Args->x;
	mouse_y = Args->y;
	GameUtils::NormalizeMousePos(startCfg.winWidth, startCfg.winHeight, Args->x, Args->y, normalizedMousePos.x, normalizedMousePos.y);
	glm::vec3 camPos = glm::vec3(Cam.GetPosition().x, Cam.GetPosition().y, Cam.GetPosition().z);
	rayDir = GameUtils::CalcCamRay(normalizedMousePos, Cam.GetProjection(), Cam.GetView());

	/* mouse cursor coordinates on XY plane  (z==0.0f) */
	mouse2dWorldPosition.x = (rayDir.x * ((-camPos.z) / rayDir.z)) + camPos.x;
	mouse2dWorldPosition.y = (rayDir.y * ((-camPos.z) / rayDir.z)) + camPos.y;
};

void CGame::DrawAxes(void){
	//render Axis 
	const float length = AXES_LENGTH;
	vsml.pushMatrix(VSMathLib::MODEL);
	float xa[6] = { -length, 0.0f, 0.0f, length, 0.0f, 0.0f };
	float ya[6] = { 0.0f, -length, 0.0f, 0.0f, length, 0.0f };
	float za[6] = { 0.0f, 0.0f, length, 0.0f, 0.0f, -length };
	basicShader.setUniform("texCount", 0);
	shapeRender.SetColor(red);
	shapeRender.DrawLine(xa, 2);
	shapeRender.SetColor(green);
	shapeRender.DrawLine(ya, 2);
	shapeRender.SetColor(blue);
	shapeRender.DrawLine(za, 2);

	vsml.popMatrix(VSMathLib::MODEL);
}


CCamera& CGame::GetCamera(){
	return this->Cam;
}

void CGame::GetWindowSize(uint32 &width, uint32 &height){
	width = this->startCfg.winWidth;
	height = this->startCfg.winHeight;
}

void CGame::GetMousePos(uint32 &x, uint32 &y){
	x = this->mouse_x;
	y = this->mouse_y;
}

void CGame::GetNormalizedMousePos(float &x, float &y){
	x = this->normalizedMousePos.x;
	y = this->normalizedMousePos.y;
}

void CGame::GetMouse2dWorldPositon(float &x, float &y){
	x = this->mouse2dWorldPosition.x;
	y = this->mouse2dWorldPosition.y;
}

CScene& CGame::GetScene(){
	return MainScene;
}

CTextureManager& CGame::GetTextureManager(){
	return textureMan;
}

VSLogLib& CGame::GetLog(){
	return log;
}

std::string& CGame::GetRenderLog(){
	return renderLogStr;
}