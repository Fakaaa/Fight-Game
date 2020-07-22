#ifndef STAGE
#define STAGE

#include "gameLoop.h"

namespace Stage {

	enum StageID{
		Airport,
		NightClub,
		Forest,
		Port
	};

	struct Stages {
		Texture2D bg;
		StageID map;
		Rectangle floor;
		Rectangle limitLeft;
		Rectangle limitRight;
	};

	extern Stages scenario;

	extern void InitializeStage();
	extern void DrawBackGround();
	extern void LoadAssets();
	extern void UnloadAssets();
}
#endif // !STAGE