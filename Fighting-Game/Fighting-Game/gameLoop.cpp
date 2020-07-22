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

			ClearBackground(BLACK);

			BeginDrawing();

			DrawThings();

			Inputs();

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

		Players::InputsPlayer();

	}

	void CloseKey() {
		if (IsKeyPressed(KEY_ESCAPE))
			WindowShouldClose();
	}
}