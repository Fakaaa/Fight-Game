#include "stage.h"

namespace Stage {

	Stages scenario;

	void InitializeStage() {
		
		scenario.map = Airport;

		LoadAssets();
		scenario.floor = {0.0f , screenHeight - 60 , screenWidht , 10};
		scenario.limitLeft = { 0.0f , 0.0f , 10 , screenHeight };
		scenario.limitRight = { screenWidht - 10 , 0.0f , 10 , screenHeight };
	}

	void DrawBackGround() {
		DrawTexture(scenario.bg, 0, 0, WHITE);
		DrawRectangleLinesEx(scenario.floor, 2, RED);
	}

	void LoadAssets() {

		Image rescale;

		if (scenario.map == Airport) {
			rescale = LoadImage("assets/AIRPORT.png");
			ImageResize(&rescale, screenWidht, screenHeight);
			scenario.bg = LoadTextureFromImage(rescale);
			UnloadImage(rescale);
		}
		if (scenario.map == NightClub) {
			rescale = LoadImage("assets/NIGHTCLUB.png");
			ImageResize(&rescale, screenWidht, screenHeight);
			scenario.bg = LoadTextureFromImage(rescale);
			UnloadImage(rescale);
		}
		if (scenario.map == Forest) {
			rescale = LoadImage("assets/FOREST.png");
			ImageResize(&rescale, screenWidht, screenHeight);
			scenario.bg = LoadTextureFromImage(rescale);
			UnloadImage(rescale);
		}
		if (scenario.map == Port) {
			rescale = LoadImage("assets/PORT.png");
			ImageResize(&rescale, screenWidht, screenHeight);
			scenario.bg = LoadTextureFromImage(rescale);
			UnloadImage(rescale);
		}
	}
	
	void UnloadAssets() {
		UnloadTexture(scenario.bg);
	}
}