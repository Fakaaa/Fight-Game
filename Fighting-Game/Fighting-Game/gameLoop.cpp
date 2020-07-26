#include "gameLoop.h"

namespace GL {

	void InitializeAll(){

		Screen::InitializeScreen();
		SetTargetFPS(120);
		//MENU
		//desp lo siguiente
		Stage::InitializeStage();

		Players::InitializePlayers();
	}

	void DeInitializeAll() {
		Players::UnloadTextures(Players::player1);
		Players::UnloadTextures(Players::playerDummy);
		Stage::UnloadAssets();
	}

	void Loop() {
		
		InitializeAll();

		while (!WindowShouldClose()){

			Players::CalcDeltaTime();

			Stage::animBackGround();

			Players::CalcFrameAnimPlayers(Players::player1);
			Players::CalcFrameAnimPlayers(Players::playerDummy);

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
		Players::DrawPlayers(Players::playerDummy);
		Players::DrawPlayers(Players::player1);
	}

	void Inputs() {
		
		CloseKey();

		Players::InputsPlayer1(Players::player1);
		Players::InputsPlayer2(Players::playerDummy);

		Players::CheckOnFloor(Players::player1);
		Players::CheckOnFloor(Players::playerDummy);

		Players::PhysicsPlayers(Players::player1,Players::playerDummy);
	}

	void CloseKey() {
		if (IsKeyPressed(KEY_ESCAPE))
			WindowShouldClose();
	}
}