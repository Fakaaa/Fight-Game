#ifndef GAMELOOP
#define GAMELOOP

#include "raylib.h"
#include "players.h"
#include "screen.h"

using namespace Screen;
using namespace Players;

namespace GL {

	extern void InitializeAll();
	extern void Loop();
}
#endif // !GAMELOOP