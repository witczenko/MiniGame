#include "Input.h"


CInputInterface::CInputInterface()
{
	CInputManager::GetInputManager().AddListener(this);
}


CInputInterface::~CInputInterface()
{
	CInputManager::GetInputManager().RemoveListener(this);
}





//CINPUTMANAGER CLASS

CInputManager::~CInputManager(){
	Args.button = MNone;
}

void CInputManager::Update(uint32 dt){

	//Do stuff with listeners 
	for (uint32 i = 0; i < m_Listeners.size(); ++i)
		m_Listeners[i]->PerFrame(dt);


	while (SDL_PollEvent(&event)){

		// 'X' button
		if (event.type == SDL_QUIT) m_Listeners[0]->OnWindowExit();

		switch (event.type){
		case SDL_KEYDOWN:{
							 Key = event.key.keysym.sym;
							 //Do stuff with listeners 
							 for (uint32 i = 0; i < m_Listeners.size(); ++i)
								 m_Listeners[i]->OnKeyDown(&Key);
							 
							 
		}
		break;

		case SDL_MOUSEMOTION:{
								 Args.dx = Args.x - event.motion.x;
								 Args.dy = Args.y - event.motion.y;

								 Args.x = event.motion.x;
								 Args.y = event.motion.y;

								 //Do stuff with listeners  
								 for (uint32 i = 0; i < m_Listeners.size(); ++i)
									 m_Listeners[i]->OnMouseMove(&Args);
		}
		break;

		case SDL_MOUSEBUTTONDOWN:{ 
									 if (event.button.button == SDL_BUTTON_LEFT) Args.button = MLeft; 
									 if (event.button.button == SDL_BUTTON_RIGHT) Args.button = MRight; 
									 
									 //Do stuff with listeners 
									 for (uint32 i = 0; i < m_Listeners.size(); ++i)
										 m_Listeners[i]->OnMouseButtonDown(&Args);

									 //Args.button = MNone;
		}
		break;

		case SDL_MOUSEBUTTONUP:{
								   for (uint32 i = 0; i < m_Listeners.size(); ++i)
									   m_Listeners[i]->OnMouseButtonUp(&Args);
								   Args.button = MNone;
		}
		break;

		case SDL_MOUSEWHEEL:{
								if (event.wheel.y > 0){
									for (uint32 i = 0; i < m_Listeners.size(); ++i)
										m_Listeners[i]->OnMouseWheelForward();
								}
								else{
									for (uint32 i = 0; i < m_Listeners.size(); ++i)
										m_Listeners[i]->OnMouseWheelBackward();
								}
								
		}
		break;
		}// end of event.type switch
	}// end of while loop

}

void CInputManager::AddListener(CInputInterface* pListener){
	m_Listeners.push_back(pListener);
}

void CInputManager::RemoveListener(CInputInterface* pListener){
	for (uint32 i = 0; i < m_Listeners.size(); ++i){
		if (m_Listeners[i] == pListener){
			m_Listeners.erase(m_Listeners.begin() + i);
		}
	}
}