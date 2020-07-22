#ifndef GAMELOOP
#define GAMELOOP

#include "raylib.h"
#include "players.h"
#include "stage.h"
#include "screen.h"

namespace GL {

	extern void InitializeAll();
	extern void Loop();
	extern void Inputs();
	extern void DrawThings();
	extern void DeInitializeAll();
	extern void CloseKey();
}
#endif // !GAMELOOP