#include "Game.h"
#include <glm/gtc/type_ptr.hpp>

#include "Animation.h"

#define AXES_LENGTH (10e5)

CTextureManager textureMan;
CSpriteAnimation *dupa;

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
MainScene(NULL),
Map1(NULL),
Player1(NULL),

vsml(*VSMathLib::getInstance())
{
	log.addMessage("Start logging...");	
	/* Prepare initial config (basic settings) */
	startCfg.fullScreen = false;
	startCfg.winHeight = HEIGHT;
	startCfg.winWidth = WIDTH;
	startCfg.vSync = true;

	LoadConfig("config.xml");
	//ParseArgs(argc, args);
}


CGame::~CGame()
{
	log.dumpToFile("GAME_LOG.txt");
	delete Cam;
	delete Map1;
	delete Player1;
	delete MainScene;

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

	//INIT SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
		std::cerr << SDL_GetError();
		log.addMessage(SDL_GetError());		
		log.dumpToFile("GAME_LOG.txt");
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
						  Win = SDL_CreateWindow("MiniGame", 0, 100, 
												  startCfg.winWidth, startCfg.winHeight, SDL_WINDOW_OPENGL);
	break;
	}
	
	if (Win == 0){
		std::cerr << SDL_GetError();
		log.addMessage(SDL_GetError());
		log.dumpToFile("GAME_LOG.txt");
		return false;
	}

	MainGlContext = SDL_GL_CreateContext(Win);

	/* GLEW STUFF */
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();

	if (glewError == GLEW_OK){
		if (!glewIsSupported("GL_ARB_vertex_buffer_object"))
		{
			std::cerr <<"VBO is not supported by your graphic card\n";
			log.addMessage("VBO is not supported by your graphic card");
			log.dumpToFile("GAME_LOG.txt");	
		}	

		if (!glewIsSupported("GL_EXT_direct_state_access")){
			std::cerr << "DUPA is not supported\n";
		}

		if (!glewIsSupported("GL_ARB_uniform_buffer_object")){
			std::cerr << "UBO is not supported\n";
		}

		if (!glewIsSupported("GL_VERSION_3_1"))
		{
			std::cerr << "OpenGL 3.1 not supported!\n";	
			log.addMessage("OpenGL 3.1 not supported!\n(twoja karta graficzna jest stara jak skala, lub masz stare drivery...)");
			log.dumpToFile("GAME_LOG.txt");
		}

		if (startCfg.vSync){
			if (SDL_GL_SetSwapInterval(1) < 0)
					VSLOG(log, "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError())
		}


		//GL SETTINGS 
		// Enable depth test
		VSGLInfoLib::getGeneralInfo();

		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		glEnable(GL_MULTISAMPLE);
		glClearColor(.3f, .3f, .3f, 1.0f);

		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//wireframe mode
		//glPolygonMode(GL_FRONT, GL_LINE);
		//glPolygonMode(GL_BACK, GL_LINE);
	}
	else{	
		std::cerr << glewGetErrorString(glewError); 
		log.addMessage((const char*)glewGetErrorString(glewError));
		log.dumpToFile("GAME_LOG.txt");
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
		//Log
		std::cerr << "Cant load fonts/couriernew10 font...";
		log.addMessage("Cant load fonts/couriernew10 font...");
	}

	basicFont.setFixedFont(true);
	basicFont.setColor(1.0f, 0.5f, 0.25f, 1.0f);
	debugInfo = basicFont.genSentence();

	shapeRender.Init();
}

void CGame::SetupShaders(){
	// Shader for fonts and models
	basicShader.init();
	basicShader.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/dirlightdiffambpix.vert");
	basicShader.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/dirlightdiffambpix.frag");

	// set semantics for the shader variables
	basicShader.setProgramOutput(0, "outputF");
	basicShader.setVertexAttribName(VSShaderLib::VERTEX_COORD_ATTRIB, "position");
	basicShader.setVertexAttribName(VSShaderLib::TEXTURE_COORD_ATTRIB, "texCoord");
	basicShader.setVertexAttribName(VSShaderLib::NORMAL_ATTRIB, "normal");

	basicShader.prepareProgram();

	basicShader.useProgram();
	//VSGLInfoLib::getProgramInfo(basicShader.getProgramIndex());
	//VSGLInfoLib::getUniformsInfo(basicShader.getProgramIndex());
	printf("%s\n", basicShader.getAllInfoLogs().c_str());
	
	//basicShader.setStandardMaterialUniforms();
	basicShader.setUniform("texUnit", 0);

	
}


bool CGame::Run(){

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

	Cam = new CCamera(FOV, ASPECT, 0.1f, 250.0f);
	MainScene = new CScene;
	Map1 = new CMapHandler;
	Player1 = new CPlayer;
	
	MainScene->Init();
	textureMan.Init(); // <-- Here all textures are loaded

	uint32 TEXTURE_1 = textureMan.GetTexture("gfx/grid_color.png");
	uint32 TEXTURE_2 = textureMan.GetTexture("gfx/bg.jpg");
	uint32 TEXTURE_3 = textureMan.GetTexture("gfx/cursor.png");

	glm::vec3 init_pos1 = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 init_pos2 = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 init_pos3 = glm::vec3(0.0f, 0.0f, -0.1f);
	glm::vec3 init_pos4 = glm::vec3(-1.0f, 0.0f, 1.0f);

	CSpriteAnimation *spriteAnim = new CSpriteAnimation();

	Player1->SetPos(init_pos1);
	bool loaded = spriteAnim->LoadAnimation("gfx/Opening/Opening__00",7);
	spriteAnim->SetPos(init_pos1);
	spriteAnim->SetFPS(24);
	spriteAnim->SetHeight(0.4);
	spriteAnim->SetWidth(0.4);

	/*dupa = new CSpriteAnimation();
	dupa->LoadAnimation("gfx/Opening/Opening__00", 7);
	dupa->SetPos(init_pos3);
	dupa->SetFPS(24);
	dupa->SetHeight(0.4);
	dupa->SetWidth(0.4);*/


	Player1->sprite_anim = spriteAnim;

	//Map1->LoadTxtMap("maps/map1.txt");
	//Map1->AddToScene(MainScene, &textureMan);
	//Map1->DisplayTiles();

	MainScene->AddObject(new CSprite(init_pos2, 1.5f * 5, 1.0f * 5, TEXTURE_2), GameObject::SPRITE);
	//->AddObject(dupa, GameObject::SPRITE_ANIM);
	MainScene->AddObject(Player1, GameObject::PLAYER);
	

	//MainScene->AddObject(spriteAnim, GameObject::SPRITE_ANIM);

	char fps[64] = "";
	uint32 acc = 0;

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
	}


	return true;
}

void CGame::Update(uint32 dt){
	CInputManager::GetInputManager().Update(dt);
	MainScene->Update(dt);

}

void CGame::Draw(uint32 dt){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	basicShader.useProgram();

	static int time = 0;
	time += dt;

	vsml.loadIdentity(VSMathLib::VIEW);
	vsml.loadIdentity(VSMathLib::MODEL);

	// set camera
	vsml.lookAt(Cam->GetPosition().x, Cam->GetPosition().y, Cam->GetPosition().z, 
				  Cam->GetTarget().x, Cam->GetTarget().y, Cam->GetTarget().z, 0, 1, 0);

	
	vsml.pushMatrix(VSMathLib::MODEL);

	basicShader.setUniform("texCount", 1);
	MainScene->Draw();

	vsml.popMatrix(VSMathLib::MODEL);

	DrawAxes();
	basicFont.renderSentence(10, 10, debugInfo);	

	SDL_GL_SwapWindow(Win);
}



void CGame::OnKeyDown(const SDL_Keycode *Key){
	if (*Key == SDLK_ESCAPE){
		GameRunning = false;
	}else
	if (*Key == SDLK_1) {
		Cam->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
		Cam->SetTarget(glm::vec3(0.0f, 0.0f, 0.0f));
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
			glm::vec3 CamPos = Cam->GetPosition();
			glm::vec3 CamTarget = Cam->GetTarget();

			CamPos.x += (float32)(Args->dx / 200.0f)*CAM_SPEED;
			CamPos.y -= (float32)(Args->dy / 200.0f)*CAM_SPEED;


			CamTarget.x += (float32)(Args->dx / 100.0f)*CAM_SPEED;
			CamTarget.y -= (float32)(Args->dy / 59.0f)*CAM_SPEED;

			Cam->SetPosition(CamPos);
			Cam->SetTarget(CamTarget);
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
	glm::vec3 CamPos = Cam->GetPosition();
	CamPos.z += 0.6f;
	Cam->SetPosition(CamPos);
}

void CGame::OnMouseWheelForward(){
	glm::vec3 CamPos = Cam->GetPosition();
	if ((CamPos.z - 0.6) > 0.1)
	{
		CamPos.z -= 0.6f;
		Cam->SetPosition(CamPos);
	}
}

void CGame::CalculateMousePos(const MouseArgs *Args){
	/* normalize mouse position  */
	mouse_x = Args->x;
	mouse_y = Args->y;
	GameUtils::NormalizeMousePos(startCfg.winWidth, startCfg.winHeight, Args->x, Args->y, normalizedMousePos.x, normalizedMousePos.y);
	glm::vec3 camPos = glm::vec3(Cam->GetPosition().x, Cam->GetPosition().y, Cam->GetPosition().z);
	rayDir = GameUtils::CalcCamRay(normalizedMousePos, Cam->GetProjection(), Cam->GetView());

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


CCamera *CGame::GetCamera(){
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