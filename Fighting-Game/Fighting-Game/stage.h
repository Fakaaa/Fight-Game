#ifndef STAGE
#define STAGE

#include "gameLoop.h"

namespace Stage {

	enum StageID{
		Airport,
		NightClub,
		Forest,
		Cascade
	};

	struct Stages {
		Texture2D bg;
		StageID map;
		Rectangle floor;
		Rectangle limitLeft;
		Rectangle limitRight;
	};

	extern Stages scenario;

	extern Vector2 pos;
	extern Rectangle frameRecStage;
	extern int framesAnim;
	extern int currentFrame;
	extern int framesCounter;
	extern int framesSpeed;

	extern void InitializeStage();
	extern void DrawBackGround();
	extern void animBackGround();
	extern void LoadAssets();
	extern void UnloadAssets();
}
#endif // !STAGE