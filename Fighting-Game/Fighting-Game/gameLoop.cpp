#include "gameLoop.h"

namespace GL {

	void InitializeAll(){

		Screen::InitializeScreen();
		SetTargetFPS(60);
		//MENU
		//desp lo siguiente
		Stage::InitializeStage();

		Players::InitializePlayers();
	}

	void DeInitializeAll() {
		//Players::UnloadTextures();
		Stage::UnloadAssets();
	}

	void Loop() {
		
		InitializeAll();

		while (!WindowShouldClose()){

			Players::CalcDeltaTime();

			Players::CalcFrameAnimPlayer1();

			ClearBackground(BLACK);

			BeginDrawing();

			Inputs();

			DrawThings();

			EndDrawing();
		}

		DeInitializeAll();
		CloseWindow();
	}

	void DrawThings() {
		Stage::DrawBackGround();
		Players::DrawPlayers();
	}

	void Inputs() {
		
		CloseKey();

		Players::PhysicsPlayers();
	}

	void CloseKey() {
		if (IsKeyPressed(KEY_ESCAPE))
			WindowShouldClose();
	}
}