#include "players.h"
#include "stage.h"

namespace Players {

	Pjs player1;
	Pjs playerDummy;

	float punchLeght = 140.0f;
	float punchHeight = 60.0f;
	float blockSize = 100.0f;
	float kickLenght = 195.0f;
	float kickHeight = 60.0f;

	bool inFloor = false;

	int framesAnim = 0;
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
			player1.characters.colliders[0] = {player1.collider.x + 20, player1.collider.y + 50, punchLeght, punchHeight };
			player1.characters.colliders[1] = {player1.collider.x + (player1.collider.width - 70), player1.collider.y + 100, blockSize, player1.collider.height / 2 };
			player1.characters.colliders[2] = { player1.collider.x - (kickLenght / 2), player1.collider.y + +110, kickLenght, kickHeight };
		}

		if (playerDummy.champSelected == Jack) {
			playerDummy.characters.champ = Jack;
			playerDummy.characters.colliders[0] = { playerDummy.collider.x + 20, playerDummy.collider.y + 100, 140, 60 };
		}

		player1.maxHeightJump = 80.0f;
		player1.maxDashDistance = 200.0f;
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
			
			rescale = LoadImage("assets/CROUCH_JACK.png");
			ImageResize(&rescale, ((player1.collider.width + 50) * 4), (player1.collider.height - 120));
			player1.characters.anims[1] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/WALK_RIGHT.png");
			ImageResize(&rescale, ((player1.collider.width + 50) * 4), (player1.collider.height));
			player1.characters.anims[2] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/JUMP_JACK.png");
			ImageResize(&rescale, ((player1.collider.width + 50) * 8), (player1.collider.height));
			player1.characters.anims[3] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/BLOCK_JACK.png");
			ImageResize(&rescale, ((player1.collider.width + 50) * 6), (player1.collider.height));
			player1.characters.anims[4] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/CROUCH_BLOCK.png");
			ImageResize(&rescale, ((player1.collider.width + 50) * 4), (player1.collider.height - 120));
			player1.characters.anims[5] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/PUNCH_JACK.png");
			ImageResize(&rescale, ((player1.collider.width + 50) * 8), (player1.collider.height));
			player1.characters.anims[6] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/WALK_LEFT.png");
			ImageResize(&rescale, ((player1.collider.width + 50) * 4), (player1.collider.height));
			player1.characters.anims[7] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/KICK_JACK.png");
			ImageResize(&rescale, ((player1.collider.width + 50) * 12), (player1.collider.height));
			player1.characters.anims[8] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);
		}
	}

	void UnloadTextures() {
		UnloadTexture(player1.characters.anims[0]);
		UnloadTexture(player1.characters.anims[1]);
		UnloadTexture(player1.characters.anims[2]);
		UnloadTexture(player1.characters.anims[3]);
		UnloadTexture(player1.characters.anims[4]);
		UnloadTexture(player1.characters.anims[5]);
		UnloadTexture(player1.characters.anims[6]);
		UnloadTexture(player1.characters.anims[7]);
		UnloadTexture(player1.characters.anims[8]);
	}

	void CalcFrameAnimPlayer1() {
		framesCounter++;
		if (framesCounter >= (60 / framesSpeed))
		{
			framesCounter = 0;
			currentFrame++;

			if (currentFrame > framesAnim) currentFrame = 0;

			player1.frameRec.x = ((float)currentFrame) * ((float)player1.characters.anims[0].width / framesAnim);
		}
		if (framesSpeed > MAX_FRAME_SPEED) { framesSpeed = MAX_FRAME_SPEED; }
		else if (framesSpeed < MIN_FRAME_SPEED) { framesSpeed = MIN_FRAME_SPEED; }
	}


	void DrawPlayers() {
		DrawRectangleLinesEx(player1.collider, 2, GREEN);
		DrawRectangleLinesEx(player1.characters.colliders[2], 2, VIOLET);
		DrawRectangleLinesEx(player1.characters.colliders[0], 2, YELLOW);

		if (player1.state.STATE_IDLE) {
			DrawTextureRec(player1.characters.anims[0], player1.frameRec, player1.Pos, WHITE);
		}
		if (player1.state.STATE_CROUCH) {
			if (!player1.state.STATE_BLOCK_CROUCH) {
				DrawTextureRec(player1.characters.anims[1], player1.frameRec, player1.Pos, WHITE);
			}
			else {
				DrawTextureRec(player1.characters.anims[5], player1.frameRec, player1.Pos, WHITE);
				DrawRectangleLinesEx(player1.characters.colliders[1], 2, WHITE);
			}
		}
		if (player1.state.STATE_RIGHTW) {
			DrawTextureRec(player1.characters.anims[2], player1.frameRec, player1.Pos, WHITE);
		}
		if (player1.state.STATE_JUMP) {
			DrawTextureRec(player1.characters.anims[3], player1.frameRec, player1.Pos, WHITE);
		}
		if (player1.state.STATE_BLOCK && !player1.state.STATE_CROUCH) {
			DrawTextureRec(player1.characters.anims[4], player1.frameRec, player1.Pos, WHITE);
			DrawRectangleLinesEx(player1.characters.colliders[1], 2, WHITE);
		}
		if (player1.state.STATE_PUNCH) {
			DrawTextureRec(player1.characters.anims[6], player1.frameRec, player1.Pos, WHITE);
		}
		if (player1.state.STATE_LEFTW) {
			DrawTextureRec(player1.characters.anims[7], player1.frameRec, player1.Pos, WHITE);
		}
		if (player1.state.STATE_KICK) {
			DrawTextureRec(player1.characters.anims[8], player1.frameRec, player1.Pos, WHITE);
		}

		DrawRectangleLinesEx(player1.frameRec, 2, RED);
		//DrawRectangleLinesEx(playerDummy.collider, 2, RED);
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
		if (player1.state.STATE_PUNCH) {
			framesSpeed = 8;
		}
		if (player1.state.STATE_KICK) {
			framesSpeed = 8;
		}
		if (player1.state.STATE_JUMP) {
			framesSpeed = 6;
		}
		if (player1.state.STATE_RIGHTW) {
			framesSpeed = 5;
		}
		if (player1.state.STATE_LEFTW) {
			framesSpeed = 5;
		}
		if (player1.state.STATE_BLOCK) {
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
			player1.state.STATE_RIGHTW = false;
			player1.state.STATE_LEFTW = false;
			player1.state.STATE_BLOCK = false;
			player1.state.STATE_CROUCH = false;
			player1.state.STATE_PUNCH = false;
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
				if (player1.state.STATE_JUMP && inFloor) {
					currentFrame = 8;
				}
			}
			if (!player1.state.STATE_PUNCH && !player1.state.STATE_CROUCH && !player1.state.STATE_BLOCK && !player1.state.STATE_JUMP && !player1.state.STATE_KICK && !player1.state.STATE_LEFTW && !player1.state.STATE_RIGHTW) {
				player1.state.STATE_IDLE = true;
				player1.frameRec.width = (float)(player1.characters.anims[0].width / 8);
				framesAnim = 8;
			}
			else {
				player1.state.STATE_IDLE = false;
			}
		}
		
		//SALTO IN ACTION
		if (player1.state.STATE_JUMP) {
			framesAnim = 8;
			player1.collider.y -= (player1.maxHeightJump * DELTA_TIME) * 8;
		}

		//CROUCH BEGIN
		if (IsKeyDown(KEY_S)) {
			if (inFloor) {
				player1.state.STATE_CROUCH = true;
				player1.state.STATE_EXIT_C = false;
				framesAnim = 2;

				if (IsKeyDown(KEY_J)) {
					player1.state.STATE_BLOCK_CROUCH = true;
				}
				else {
					player1.state.STATE_BLOCK_CROUCH = false;
				}
			}
		}
		else
			player1.state.STATE_CROUCH = false;

		//CROUCH IN ACTION
		if (inFloor) {
			if (player1.state.STATE_CROUCH) {
				player1.collider.height = 190;
				player1.frameRec.height = 190;
				player1.frameRec.width = (float)(player1.characters.anims[1].width / 4);
				if(inFloor)
					player1.collider.y = 470;

				if (player1.state.STATE_BLOCK_CROUCH) {
					player1.characters.colliders[1].x = player1.collider.x + (player1.collider.width - 70);
				}
				else {
					player1.characters.colliders[1].x = player1.collider.x;
					player1.characters.colliders[1].y = player1.collider.y;
				}
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
				player1.frameRec.height = 340;
			}
		}

		//MOVE SIDES

		if (!player1.state.STATE_BLOCK) {
			if (IsKeyDown(KEY_D)) {
				player1.state.STATE_RIGHTW = true;
				player1.state.STATE_PUNCH = false;
			}
			else{
				player1.state.STATE_RIGHTW = false;
			}
			if (IsKeyDown(KEY_A)) {
				player1.state.STATE_LEFTW = true;
				player1.state.STATE_PUNCH = false;
			}
			else {
				player1.state.STATE_LEFTW = false;
			}
		}
		
		if (player1.state.STATE_LEFTW) {
			player1.collider.x -= 4.5f;
			if (inFloor) {
				framesAnim = 4;
				framesSpeed = 3;
			}
		}

		if (player1.state.STATE_RIGHTW) {
			player1.collider.x += 4.5f;
			if (inFloor) {
				framesAnim = 4;
				framesSpeed = 3;
			}
		}

		//BLOCK DAMAGE

		if (!player1.state.STATE_LEFTW && !player1.state.STATE_RIGHTW) {
			if (IsKeyDown(KEY_J)) {
				player1.state.STATE_BLOCK = true;
				player1.state.STATE_EXIT_B = false;
			}
			else {
				player1.state.STATE_BLOCK = false;
			}
		}

		if (inFloor) {
			if (player1.state.STATE_BLOCK) {
				framesAnim = 8;
				player1.characters.colliders[1].x = player1.collider.x + (player1.collider.width - 70);
			}
			else {
				if (!player1.state.STATE_BLOCK && !player1.state.STATE_EXIT_B) {
					player1.state.STATE_EXIT_B = true;
				}
				player1.characters.colliders[1].x = player1.collider.x;
				player1.characters.colliders[1].y = player1.collider.y;
			}
		}

		//PUNCH
		if (!player1.state.STATE_LEFTW && !player1.state.STATE_RIGHTW && !player1.state.STATE_BLOCK && !player1.state.STATE_JUMP && !player1.state.STATE_CROUCH) {
			if (IsKeyPressed(KEY_G)) {
				if (inFloor) {
					framesAnim = 6;
					currentFrame = 0;

					player1.frameRec.width += player1.frameRec.width - 100;
					
					player1.state.STATE_PUNCH = true;
					player1.state.STATE_EXIT_P = false;
				}
			}
		}

		if (inFloor) {
			if (player1.state.STATE_PUNCH) {
				player1.characters.colliders[0].x = (player1.collider.x - 40) + player1.characters.colliders[0].width;
				if (currentFrame == 6)
					player1.state.STATE_PUNCH = false;
			}
			else {
				if (!player1.state.STATE_PUNCH && !player1.state.STATE_EXIT_P) {
					player1.state.STATE_EXIT_P = true;
				}
				player1.characters.colliders[0] = { player1.collider.x, player1.collider.y + 50, punchLeght, punchHeight };
			}
		}

		//KICK

		//if (!player1.state.STATE_LEFTW && !player1.state.STATE_RIGHTW && !player1.state.STATE_BLOCK && !player1.state.STATE_JUMP && !player1.state.STATE_CROUCH && player1.state.STATE_PUNCH) {
		//}
		if (IsKeyPressed(KEY_H)) {
			if (inFloor) {
				framesAnim = 6;
				currentFrame = 0;

				player1.frameRec.width += player1.frameRec.width - 120;

				player1.state.STATE_KICK = true;
				player1.state.STATE_EXIT_K = false;
			}
		}

		if (inFloor) {
			if (player1.state.STATE_KICK) {
				player1.characters.colliders[2].x = (player1.collider.x - punchLeght) + player1.characters.colliders[2].width;
				if(currentFrame == 6)
					player1.state.STATE_KICK = false;
			}
			else {
				if (!player1.state.STATE_KICK && !player1.state.STATE_EXIT_K) {
					player1.state.STATE_EXIT_K = true;
				}
				player1.characters.colliders[2] = { player1.collider.x - (kickLenght / 2), player1.collider.y + 110, kickLenght, kickHeight };
			}
		}

	}
}