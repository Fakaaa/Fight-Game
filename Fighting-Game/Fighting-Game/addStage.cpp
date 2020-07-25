#include "stage.h"

namespace Stage {

	Stages scenario;
	Rectangle frameRecStage;
	Vector2 pos;

	int framesAnim = 0;
	int currentFrame = 0;
	int framesCounter = 0;
	int framesSpeed = 8;

	void InitializeStage() {
		
		scenario.map = Cascade;
		frameRecStage = {0.0f,0.0f, screenWidht,screenHeight};
		pos = {0.0f,0.0f};

		LoadAssets();
		scenario.floor = {0.0f , screenHeight - 60 , screenWidht , 10};
		scenario.limitLeft = { 0.0f , 0.0f , 10 , screenHeight };
		scenario.limitRight = { screenWidht - 10 , 0.0f , 10 , screenHeight };
	}

	void DrawBackGround() {
		DrawTextureRec(scenario.bg,frameRecStage,pos,WHITE);


		//DrawRectangleLinesEx(scenario.floor, 2, RED);
		//DrawRectangleLinesEx(frameRecStage, 2, RED);
	}

	void animBackGround() {
		framesCounter++;
		if (framesCounter >= (60 / framesSpeed))
		{
			framesCounter = 0;
			currentFrame++;

			if (currentFrame > framesAnim) currentFrame = 0;

			frameRecStage.x = ((float)currentFrame) * ((float)scenario.bg.width / framesAnim);
		}
		if (framesSpeed > MAX_FRAME_SPEED) { framesSpeed = MAX_FRAME_SPEED; }
		else if (framesSpeed < MIN_FRAME_SPEED) { framesSpeed = MIN_FRAME_SPEED; }
	}

	void LoadAssets() {

		Image rescale;

		if (scenario.map == Airport) {
			framesAnim = 4;
			currentFrame = 0;
			scenario.bg = LoadTexture("assets/AIRPORT.png");
		}
		if (scenario.map == NightClub) {
			framesAnim = 4;
			currentFrame = 0;
			scenario.bg = LoadTexture("assets/NIGHTCLUB.png");
		}
		if (scenario.map == Forest) {
			rescale = LoadImage("assets/FOREST.png");
			ImageResize(&rescale, screenWidht, screenHeight);
			scenario.bg = LoadTextureFromImage(rescale);
			UnloadImage(rescale);
		}
		if (scenario.map == Cascade) {
			framesAnim = 4;
			currentFrame = 0;
			scenario.bg = LoadTexture("assets/CASCADE.png");
		}
	}
	
	void UnloadAssets() {
		UnloadTexture(scenario.bg);
	}
}