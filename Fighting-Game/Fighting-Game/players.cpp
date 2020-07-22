#include "players.h"
#include "stage.h"

namespace Players {

	Pjs player1;

	void InitializePlayers() {


		if (player1.champSelected == Jack) {
			//Texturas de Jack y sus animaciones
		}
		//Demas champions

		player1.collider = { (0.0f + 150), Stage::scenario.floor.y - 390 , 180, 380 };

	}

	void LoadTextures() {

	}

	void UnloadTextures() {

	}

	void DrawPlayers() {
		DrawRectangleLinesEx(player1.collider, 2, GREEN);
	}

	void InputsPlayer() {
		if (IsKeyDown(KEY_W))
			player1.collider.y -= 4.0f;
		//if (IsKeyDown(KEY_S))

		if (IsKeyDown(KEY_A))
			player1.collider.x -= 4.0f;
		if (IsKeyDown(KEY_D))
			player1.collider.x += 4.0f;
	}
}