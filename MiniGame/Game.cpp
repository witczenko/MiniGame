#include "Game.h"
#include "Sprite.h"

//test varibales 
static bool boxEmmiter = false;
static float angle = 0;

CGame::CGame(int argc, char* args[]) :
Win(0),
MainGlContext(NULL),
GlobalTime(0),
GameRunning(true),
mouse2DPosition(0.0f, 0.0f),
Mjoint(NULL),
lockCam(false),
mouseSprite(NULL)
{
	log.addMessage("Start logging...");	
	
	/* Prepare initial config (basic settings) */
	startCfg.fullScreen = false;
	startCfg.winHeight = HEIGHT;
	startCfg.winWidth = WIDTH;
	startCfg.vSync = true;

	LoadConfig("config.xml");
	ParseArgs(argc, args);
}


CGame::~CGame()
{
	log.dumpToFile("GAME_LOG.txt");

	delete physics;
	delete scene;
	delete Cam;
	delete tex;

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

	SDL_ShowCursor(SDL_DISABLE);

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
		glEnable(GL_CULL_FACE);
		glEnable(GL_MULTISAMPLE);
		glClearColor(.3f, .3f, .3f, 1.0f);

		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);
		glEnable(GL_BLEND);
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
	/* VS LIB */

	vsml = VSMathLib::getInstance();
	// Set both matrices to the identity matrix
	vsml->loadIdentity(VSMathLib::VIEW);
	vsml->loadIdentity(VSMathLib::MODEL);

	// set the material's block name
	//VSResourceLib::setMaterialBlockName("Material");

	// Init VSML
	vsml = VSMathLib::getInstance();
	//vsml->setUniformBlockName("Matrices");
	vsml->setUniformName(VSMathLib::PROJ_VIEW_MODEL, "projViewModelMatrix");
	vsml->setUniformName(VSMathLib::NORMAL, "normalMatrix");

	bool loaded = basicFont.load("fonts/couriernew10");
	if (loaded == false){
		//Log
		std::cerr << "Cant load fonts/couriernew10 font...";
		log.addMessage("Cant load fonts/couriernew10 font...");
	}

	basicFont.setFixedFont(true);
	basicFont.setColor(1.0f, 0.5f, 0.25f, 1.0f);
	aSentence = basicFont.genSentence();
	debugInfo = basicFont.genSentence();

	basicFont.prepareSentence(aSentence, "Wbrew powszechnej opinii skrzywienie krêgos³upa nie jest nastêpstwem z³ej postawy czy niew³aœciwych \n nawyków podczas siedzenia. Skolioza nie jest spowodowana równie¿ noszeniem plecaka czy teczki stale w jednej rêce. 85%\n skrzywieñ krêgos³upa o charakterze strukturalnym to skoliozy idiopatyczne, czyli o nieznanej przyczynie.");

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
	
	basicShader.setStandardMaterialUniforms();
	basicShader.setUniform("texUnit", 0);
}



void CGame::Update(uint32 dt){
	CInputManager::GetInputManager().Update(dt);

	
}


void CGame::Draw(uint32 dt){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//scene->Draw(Cam);

	basicShader.useProgram();

	vsml->loadIdentity(VSMathLib::VIEW);
	vsml->loadIdentity(VSMathLib::MODEL);

	// set camera
	vsml->lookAt( Cam->GetPosition().x, Cam->GetPosition().y, Cam->GetPosition().z, 
				  Cam->GetTarget().x, Cam->GetTarget().y, Cam->GetTarget().z, 0, 1, 0);
	
	//vsml->pushMatrix(VSMathLib::MODEL);
	Model2.render();
	//vsml->popMatrix(VSMathLib::MODEL);
	
	
	vsml->pushMatrix(VSMathLib::MODEL);

	angle += (dt / 10.0f);
	vsml->rotate(angle/5.0, 1.0f, 0.0f, 0.0f);
	vsml->scale(0.2, 0.2, 0.2);

	vsml->translate(VSMathLib::MODEL, 0.0f, sin(SDL_GetTicks() / 100.0f), 2.0f);
	Model1.render();
	vsml->popMatrix(VSMathLib::MODEL);

	//basicFont.setColor( 1.0f, 1.0f, 1.0f, 0.8f);		
	basicFont.renderSentence(10, 10, debugInfo);	
	basicFont.renderSentence(10, 300, aSentence);

	SDL_GL_SwapWindow(Win);
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

	vsml->loadIdentity(VSMathLib::PROJECTION);
	vsml->perspective(53.13f, ASPECT, 0.1f, 10000.0f);

	//scene = new CScene(WIDTH, HEIGHT);
	physics = new CPhysics;
	Cam = new CCamera(FOV, ASPECT, 0.1f, 250.0f);

	bool loaded = Model1.load("gfx/ico.obj");
	bool loaded2 = Model2.load("gfx/map_01.obj");
	//bool loaded = mapModel.load("gfx/ico.obj");
	Model1.addTexture(0, "gfx/grid_color.png");
	Model2.addTexture(0, "gfx/grid_color.png");

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
			if(startCfg.vSync)
				sprintf(fps, "FPS %f \nVSYNC ON", (1000.0f / dt));
			else
				sprintf(fps, "FPS %f \nVSYNC OFF", (1000.0f / dt));
			basicFont.prepareSentence(debugInfo, fps);
		}

		//Handle input
		Update(dt);

		//Draw 
		Draw(dt);
	}


	return true;
}

void CGame::OnKeyDown(const SDL_Keycode *Key){
	if (*Key == SDLK_ESCAPE) GameRunning = false;
	if (*Key == SDLK_1) {
		Cam->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
		Cam->SetTarget(glm::vec3(0.0f, 0.0f, 0.0f));
	}
	if (*Key == SDLK_2) {
		lockCam = true;
	}
	if (*Key == SDLK_3) {
		lockCam = false;
	}
	if (*Key == SDLK_4) {
		boxEmmiter = true;
	}
	if (*Key == SDLK_5) {
		boxEmmiter = false;
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

			CamPos.x += (float32)Args->dx / 100.0f;
			CamPos.y -= (float32)Args->dy / 100.0f;
			CamTarget.x += (float32)Args->dx / 100.0f;
			CamTarget.y -= (float32)Args->dy / 59.0f;

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
		if (Mjoint){
			std::cout << "Delete Mjoint" << std::endl;
			physics->DeleteJoint(Mjoint);
			Mjoint = NULL;
		}
	}
}

void CGame::OnMouseWheelBackward(){
	glm::vec3 CamPos = Cam->GetPosition();
	CamPos.z += 0.6;
	Cam->SetPosition(CamPos);
}

void CGame::OnMouseWheelForward(){
	glm::vec3 CamPos = Cam->GetPosition();
	if ((CamPos.z - 0.6) > 0.1)
	{
		CamPos.z -= 0.6;
		Cam->SetPosition(CamPos);
	}
}

void CGame::CalculateMousePos(const MouseArgs *Args){
	/* normalize mouse position  */
	NormalizeMousePos(WIDTH, HEIGHT, Args->x, Args->y, normalizedMousePos.x, normalizedMousePos.y);

	glm::vec3 camPos = glm::vec3(Cam->GetPosition().x, Cam->GetPosition().y, Cam->GetPosition().z);
	glm::vec4 mouse_clip = glm::vec4(normalizedMousePos.x, normalizedMousePos.y, -1.0, 1.0);
	glm::vec4 ray_eye = glm::inverse(Cam->GetProjection()) * mouse_clip;
	ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
	glm::vec3 ray = glm::normalize(glm::vec3(glm::inverse(Cam->GetView()) * ray_eye));

	/* mouse cursor coordinates on XY plane */
	mouse2DPosition.x = (ray.x * ((-camPos.z) / ray.z)) + camPos.x;
	mouse2DPosition.y = (ray.y * ((-camPos.z) / ray.z)) + camPos.y;
};

void CGame::NormalizeMousePos(uint32 screenWidth, uint32 screenHeight, uint32 inX, uint32 inY, float32 &outX, float32 &outY){
	outX = ((2.0f * inX) / (float)(screenWidth)) - 1.0f;
	outY = 1.0f - ((2.0f * inY) / (float)screenHeight);
}