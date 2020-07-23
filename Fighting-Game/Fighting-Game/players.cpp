#include "players.h"
#include "stage.h"

namespace Players {

	Pjs player1;
	bool inFloor = false;

	float PREVIUS_TIME = 0.0f;
	float CURRENT_TIME = 0.0f;
	float DELTA_TIME = 0.0f;

	void InitializePlayers() {


		if (player1.champSelected == Jack) {
			//Texturas de Jack y sus animaciones
		}
		//Demas champions

		player1.collider = { (0.0f + 150), Stage::scenario.floor.y - 390 , 180, 380 };
		player1.speed = {500,20};
		player1.maxHeightJump = 80.0f;
		player1.gravity = { 0.0f,-450.0f };
		player1.state.STATE_EXIT = false;
	}

	void LoadTextures() {

	}

	void UnloadTextures() {

	}

	void DrawPlayers() {
		DrawRectangleLinesEx(player1.collider, 2, GREEN);
	}

	void CalcDeltaTime() {
		PREVIUS_TIME = CURRENT_TIME;
		CURRENT_TIME = (float)GetTime();
		DELTA_TIME = CURRENT_TIME - PREVIUS_TIME;
		if (DELTA_TIME > 0.15f)
			DELTA_TIME = 0.15f;
	}

	void PhysicsPlayers() {

		InputsPlayer();

		CheckOnFloor();

		if (!inFloor) {
			player1.collider.y = player1.collider.y + player1.speed.y * DELTA_TIME;
			player1.speed.y = player1.speed.y - player1.gravity.y * (DELTA_TIME * 2);
		}
		else {
			player1.speed = {500.0f,20.0f};
			player1.collider.x = player1.collider.x;
			player1.collider.y = player1.collider.y;
			player1.state.STATE_JUMP = false;
		}
	}

	void CheckOnFloor() {
		if (CheckCollisionRecs(player1.collider, Stage::scenario.floor))
			inFloor = true;
		else
			inFloor = false;
	}

	void InputsPlayer() {

		//SALTO BEGIN
		if (inFloor){
			if (IsKeyDown(KEY_SPACE)) {
				player1.state.STATE_JUMP = true;
			}
		}
		
		//SALTO IN ACTION
		if (player1.state.STATE_JUMP) {
			player1.collider.y -= (player1.maxHeightJump * DELTA_TIME) * 8;
		}

		//CROUCH BEGIN
		if (IsKeyDown(KEY_S)) {
			player1.state.STATE_CROUCH = true;
			player1.state.STATE_EXIT = false;
		}
		else
			player1.state.STATE_CROUCH = false;

		//CROUCH IN ACTION
		if (player1.state.STATE_CROUCH) {
			player1.collider.height = 190;
		}
		else {
			if (!player1.state.STATE_CROUCH && !player1.state.STATE_EXIT) {
				if (inFloor) {
					player1.collider.y = Stage::scenario.floor.y - 380;
				}
				else {
					player1.collider.y = player1.collider.y;
				}
				player1.state.STATE_EXIT = true;
			}
			player1.collider.height = 380;
		}

		//MOVE SIDES
		if (IsKeyDown(KEY_A))
			player1.collider.x -= 4.0f;
		if (IsKeyDown(KEY_D))
			player1.collider.x += 4.0f;
	}
}