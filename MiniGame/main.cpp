#include <iostream>
#include "Game.h"

int wmain( int argc, char* args[] ){
	CGame::GetGameInstance().Run();
	return 0;
}