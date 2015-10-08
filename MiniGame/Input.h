/**
\brief Header class of CInputInterface and CInputManager
\file Input.h
\author Witczenko
*/


#ifndef INPUT_H
#define INPUT_H

#include "Types.h"
#include "SDL/SDL.h"
#include <vector>
#include <iostream>

/**
 * A enum to represent mouse buttons 
*/
enum MouseButton{
	MRight, /**< Right button */
	MLeft /**< Left button */,
	MCenter, /**< Center button (wheel) */
	MNone /**< Nothing, default state */
};

/** A structure to represent mouse state. */
struct MouseArgs
{
	uint32 x, y; /**< Mouse position on the screen*/

	int32 dx, dy; /**< Delta mouse position */

	MouseButton button; /**< Mouse button state*/

};

class CInputInterface;

/** 
 *Input Manager Class, Singleton 
*/
class CInputManager
{
public:
	~CInputManager();

	void AddListener(CInputInterface* pListener);
	void RemoveListener(CInputInterface* pListenre);
	void Update(uint32 dt);

	

	//Global Instance, should be a singleton? 
	static CInputManager & GetInputManager(){
		static CInputManager GameInputManager; return GameInputManager;
	}

private:
	bool GameExit;
	SDL_Event event;
	MouseArgs Args;
	SDL_Keycode Key;
	std::vector<CInputInterface*> m_Listeners;
};





class CInputInterface{
public:
	CInputInterface();
	~CInputInterface();

	/**
	*	\brief Function is called when the mouse is moving 
	*	\param Args mouse states 
	*	\return nothing
	*/
	virtual void OnMouseMove(const MouseArgs *Args){};

	/**
	*	\brief TODO
	*	\param TODO
	*	\return nothing
	*/
	virtual void OnMouseButtonDown(const MouseArgs *Args){};

	virtual void OnMouseButtonUp(const MouseArgs *Args){};
	
	/**
	*	\brief TODO
	*	\param TODO
	*	\return nothing
	*/
	virtual void OnMouseWheelForward(){};

	/**
	*	\brief TODO
	*	\param TODO
	*	\return nothing
	*/
	virtual void OnMouseWheelBackward(){}

	
	/**
	*	\brief TODO
	*	\param TODO
	*	\return nothing
	*/ 
	virtual void OnKeyDown(const SDL_Keycode *Key){};
	
	/**
	*	\brief TODO
	*	\param TODO
	*	\return nothing
	*/
	virtual void OnKeyUp(const SDL_Keycode *Key){};
	
	/**
	*	\brief TODO
	*	\param TODO
	*	\return nothing
	*/
	virtual void PerFrame(uint32 dt){};
	
	/**
	*	\brief TODO
	*	\param TODO
	*	\return nothing
	*/
	virtual void OnWindowExit(){};

};


#endif // INPUT_H

