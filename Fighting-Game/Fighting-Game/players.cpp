#include "players.h"
#include "stage.h"

namespace Players {

	Pjs player1;
	Pjs playerDummy;
	bool inFloor = false;

	int currentFrame = 0;
	int framesCounter = 0;
	int framesSpeed = 8;

	float PREVIUS_TIME = 0.0f;
	float CURRENT_TIME = 0.0f;
	float DELTA_TIME = 0.0f;

	void InitializePlayers() {


		player1.collider = { (0.0f + 150), Stage::scenario.floor.y - 390 , 130, 340 };
		player1.Pos = {player1.collider.x,player1.collider.y};
		player1.speed = {500,20};
		LoadTextures();
		player1.champSelected = Jack;
		player1.frameRec = {0.0f,0.0f, (float)(player1.characters.anims[0].width / 8), (float)player1.characters.anims[0].height};

		playerDummy.collider = { (0.0f + 1050), Stage::scenario.floor.y - 390 , 130, 340 };
		playerDummy.speed = player1.speed;
		playerDummy.champSelected = player1.champSelected;

		if (player1.champSelected == Jack) {
			player1.characters.champ = Jack;
			player1.characters.colliders[0] = {player1.collider.x + 20, player1.collider.y + 100, 140, 60};
		}

		if (playerDummy.champSelected == Jack) {
			playerDummy.characters.champ = Jack;
			playerDummy.characters.colliders[0] = { playerDummy.collider.x + 20, playerDummy.collider.y + 100, 140, 60 };
		}

		player1.maxHeightJump = 80.0f;
		player1.gravity = { 0.0f,-450.0f };
		player1.state.STATE_EXIT_C = false;
	}

	void LoadTextures() {

		Image rescale;

		if (player1.champSelected == Jack) {
			rescale = LoadImage("assets/JACK_IDLE.png");
			ImageResize(&rescale, ((player1.collider.width + 50) * 8), (player1.collider.height));
			player1.characters.anims[0] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);
			
			rescale = LoadImage();
		}
	}

	void UnloadTextures() {
		UnloadTexture(player1.characters.anims[0]);
	}

	void CalcFrameAnimPlayer1() {
		framesCounter++;
		if (framesCounter >= (60 / framesSpeed))
		{
			framesCounter = 0;
			currentFrame++;
			if (currentFrame > 8) currentFrame = 0;

			player1.frameRec.x = ((float)currentFrame) * ((float)player1.characters.anims[0].width / 8);
		}
		if (framesSpeed > MAX_FRAME_SPEED) { framesSpeed = MAX_FRAME_SPEED; }
		else if (framesSpeed < MIN_FRAME_SPEED) { framesSpeed = MIN_FRAME_SPEED; }
	}


	void DrawPlayers() {
		//DrawRectangleLinesEx(player1.collider, 2, GREEN);

		if (player1.state.STATE_IDLE) {
			DrawTextureRec(player1.characters.anims[0], player1.frameRec, player1.Pos, WHITE);
		}
		if (player1.state.STATE_CROUCH) {

		}
		//DrawTexture(player1.characters.anims[0], player1.collider.x, player1.collider.y, WHITE);


		//DrawRectangleLinesEx(playerDummy.collider, 2, RED);
		//DrawRectangleLinesEx(player1.characters.colliders[0], 2, YELLOW);
	}

	void CalcDeltaTime() {
		PREVIUS_TIME = CURRENT_TIME;
		CURRENT_TIME = (float)GetTime();
		DELTA_TIME = CURRENT_TIME - PREVIUS_TIME;
		if (DELTA_TIME > 0.15f)
			DELTA_TIME = 0.15f;

		if (player1.state.STATE_IDLE) {
			framesSpeed = 6;
		}
	}

	void PhysicsPlayers() {

		InputsPlayer();

		CheckOnFloor();

		//GRAVEDAD EN ACCION
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
		player1.Pos = { player1.collider.x,player1.collider.y };
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
			player1.state.STATE_IDLE = true;
		}
		
		//SALTO IN ACTION
		if (player1.state.STATE_JUMP) {
			player1.collider.y -= (player1.maxHeightJump * DELTA_TIME) * 8;
		}

		//CROUCH BEGIN
		if (IsKeyDown(KEY_S)) {
			player1.state.STATE_CROUCH = true;
			player1.state.STATE_EXIT_C = false;
		}
		else
			player1.state.STATE_CROUCH = false;

		//CROUCH IN ACTION
		if (player1.state.STATE_CROUCH) {
			player1.collider.height = 190;
			if(inFloor)
				player1.collider.y = 470;
		}
		else {
			if (!player1.state.STATE_CROUCH && !player1.state.STATE_EXIT_C) {
				if (inFloor) {
					player1.collider.y = Stage::scenario.floor.y - 340;
				}
				else {
					player1.collider.y = player1.collider.y;
				}
				player1.state.STATE_EXIT_C = true;
			}
			player1.collider.height = 340;
		}

		//MOVE SIDES
		if (IsKeyDown(KEY_A))
			player1.collider.x -= 4.5f;
		if (IsKeyDown(KEY_D))
			player1.collider.x += 4.5f;


		//PUNCH
		if (IsKeyDown(KEY_C)) {
			player1.state.STATE_PUNCH = true;
			player1.state.STATE_EXIT_P = false;
		}
		else{
			player1.state.STATE_PUNCH = false;
		}

		if (player1.state.STATE_PUNCH) {
			player1.characters.colliders[0].x = player1.collider.x + player1.characters.colliders[0].width;
		}
		else {
			if (!player1.state.STATE_PUNCH && !player1.state.STATE_EXIT_P) {
				player1.characters.colliders[0] = { player1.collider.x + 20, player1.collider.y + 100, 140, 60 };
				player1.state.STATE_EXIT_P = true;
			}
			player1.characters.colliders[0] = { player1.collider.x + 20, player1.collider.y + 100, 140, 60 };
		}

	}
}