#include <iostream>
#include "Game.h"

int wmain( int argc, char* args[] ){
	CGame::GetGameIntance().Run();
	return 0;
}