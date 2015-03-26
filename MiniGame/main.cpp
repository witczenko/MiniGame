#include <iostream>
#include "Game.h"

int wmain( int argc, char* args[] ){
	//Create Game object
	CGame Game(argc, args);

	//Run a game 
	Game.Run();

	return 0;
}