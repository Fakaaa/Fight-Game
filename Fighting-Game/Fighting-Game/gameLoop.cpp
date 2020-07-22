#include "gameLoop.h"

namespace GL {

	void InitializeAll(){

		Screen::InitializeScreen();
		//MENU
		//desp lo siguiente
		Stage::InitializeStage();
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

			EndDrawing();
		}

		DeInitializeAll();
		CloseWindow();
	}

	void DrawThings() {
		Stage::DrawBackGround();
	}

	void Inputs() {
		
		CloseKey();

	}

	void CloseKey() {
		if (IsKeyPressed(KEY_ESCAPE))
			WindowShouldClose();
	}
}