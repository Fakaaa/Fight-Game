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

	float PREVIUS_TIME = 0.0f;
	float CURRENT_TIME = 0.0f;
	float DELTA_TIME = 0.0f;

	void InitializePlayers() {


		//init player 1
		player1.collider = { (0.0f + 150), Stage::scenario.floor.y - 390 , 130, 340 };
		player1.Pos = {player1.collider.x,player1.collider.y};
		player1.speed = {400,20};
		player1.champSelected = Melissa;
		player1.inFloor = false;
		player1.characters.framesSpeed = 8;
		player1.direction = {1,0};
		LoadTextures(player1);
		
		//init player  2
		playerDummy.collider = { (0.0f + 1050), Stage::scenario.floor.y - 390 , 130, 340 };
		playerDummy.speed = {400,20};
		playerDummy.champSelected = Valhim;
		playerDummy.inFloor = false;
		playerDummy.characters.framesSpeed = 8;
		playerDummy.direction = { 0,0 };
		LoadTextures(playerDummy);

		//player 1 & 2 frameRec y boxColliders
		player1.frameRec = {0.0f,0.0f, (float)(player1.characters.animsRIGTH[0].width / 8), (float)player1.characters.animsRIGTH[0].height};
		playerDummy.frameRec = { 0.0f,0.0f, (float)(playerDummy.characters.animsRIGTH[0].width / 8), (float)playerDummy.characters.animsRIGTH[0].height };

		player1.characters.colliders[0] = { player1.collider.x + 20, player1.collider.y + 50, punchLeght, punchHeight };
		player1.characters.colliders[1] = { player1.collider.x + (player1.collider.width - 70), player1.collider.y + 100, blockSize, player1.collider.height / 2 };
		player1.characters.colliders[2] = { player1.collider.x - (kickLenght / 2), player1.collider.y + +110, kickLenght, kickHeight };

		playerDummy.characters.colliders[0] = { playerDummy.collider.x + 20, playerDummy.collider.y + 50, punchLeght, punchHeight };
		playerDummy.characters.colliders[1] = { playerDummy.collider.x + (playerDummy.collider.width - 70), playerDummy.collider.y + 100, blockSize, playerDummy.collider.height / 2 };
		playerDummy.characters.colliders[2] = { playerDummy.collider.x - (kickLenght / 2), playerDummy.collider.y + +110, kickLenght, kickHeight };

		player1.maxHeightJump = 80.0f;
		player1.maxDashDistance = 200.0f;
		player1.gravity = { 0.0f,-470.0f };
		player1.state.STATE_EXIT_C = false;

		playerDummy.maxHeightJump = 80.0f;
		playerDummy.maxDashDistance = 200.0f;
		playerDummy.gravity = { 0.0f,-470.0f };
		playerDummy.state.STATE_EXIT_C = false;

		player1.LIFE = { (float)player1.CH_MARC_LIFEBAR.width, 0.0f , (float)player1.LIFE_BAR.width, (float)player1.LIFE_BAR.height };
		playerDummy.LIFE = { static_cast<float>((screenWidht / 2) + 5), 0.0f, (float)playerDummy.LIFE_BAR.width, (float)playerDummy.LIFE_BAR.height };

	}

	void LoadTextures(Pjs& player) {

		player.characters.champ = player.champSelected;
		Image rescale;

		if (player.characters.champ == Jack) {

			rescale = LoadImage("assets/CH_MARC_JACK.png");
			ImageResize(&rescale, 120, 120);
			if (player.direction.x == 0) 
				ImageFlipHorizontal(&rescale);
			player.CH_MARC_LIFEBAR = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/JACK_IDLE.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 8), (player.collider.height));
			player.characters.animsRIGTH[0] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[0] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);
			
			rescale = LoadImage("assets/CROUCH_JACK.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 4), (player.collider.height - 120));
			player.characters.animsRIGTH[1] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[1] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/WALK_RIGHT.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 4), (player.collider.height));
			player.characters.animsRIGTH[2] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[2] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/JUMP_JACK.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 8), (player.collider.height));
			player.characters.animsRIGTH[3] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[3] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/BLOCK_JACK.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 6), (player.collider.height));
			player.characters.animsRIGTH[4] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[4] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/CROUCH_BLOCK.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 4), (player.collider.height - 120));
			player.characters.animsRIGTH[5] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[5] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/PUNCH_JACK.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 8), (player.collider.height));
			player.characters.animsRIGTH[6] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[6] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/WALK_LEFT.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 4), (player.collider.height));
			player.characters.animsRIGTH[7] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[7] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/KICK_JACK.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 12), (player.collider.height));
			player.characters.animsRIGTH[8] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[8] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);
		}

		if (player.characters.champ == Valhim) {

			rescale = LoadImage("assets/CH_MARC_VALHIM.png");
			ImageResize(&rescale, 120, 120);
			if (player.direction.x == 0)
				ImageFlipHorizontal(&rescale);
			player.CH_MARC_LIFEBAR = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/VALHIM_IDLE.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 8), (player.collider.height));
			player.characters.animsRIGTH[0] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[0] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/CROUCH_VALHIM.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 4), (player.collider.height - 120));
			player.characters.animsRIGTH[1] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[1] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/VALHIM_WALK.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 6), (player.collider.height));
			player.characters.animsRIGTH[2] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[2] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/JUMP_VALHIM.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 8), (player.collider.height));
			player.characters.animsRIGTH[3] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[3] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/BLOCK_VALHIM.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 6), (player.collider.height));
			player.characters.animsRIGTH[4] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[4] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/CROUCH_BLOCK_VALHIM.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 4), (player.collider.height - 120));
			player.characters.animsRIGTH[5] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[5] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/PUNCH_VALHIM.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 8), (player.collider.height));
			player.characters.animsRIGTH[6] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[6] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/VALHIM_LEFT.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 6), (player.collider.height));
			player.characters.animsRIGTH[7] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[7] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/KICK_VALHIM.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 12), (player.collider.height));
			player.characters.animsRIGTH[8] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[8] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);
		}

		if (player.characters.champ == Melissa) {

			rescale = LoadImage("assets/CH_MARC_MELISSA.png");
			ImageResize(&rescale, 120, 120);
			if (player.direction.x == 0)
				ImageFlipHorizontal(&rescale);
			player.CH_MARC_LIFEBAR = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/MELISSA_IDLE.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 8), (player.collider.height));
			player.characters.animsRIGTH[0] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[0] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/CROUCH_MELISSA.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 4), (player.collider.height - 120));
			player.characters.animsRIGTH[1] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[1] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/MELISSA_WALK.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 12.1f), (player.collider.height));
			player.characters.animsRIGTH[2] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[2] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/JUMP_MELISSA.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 7.9f), (player.collider.height));
			player.characters.animsRIGTH[3] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[3] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/BLOCK_MELISSA.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 6), (player.collider.height));
			player.characters.animsRIGTH[4] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[4] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/CROUCH_BLOCK_MELISSA.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 4), (player.collider.height - 120));
			player.characters.animsRIGTH[5] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[5] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/PUNCH_MELISSA.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 8), (player.collider.height));
			player.characters.animsRIGTH[6] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[6] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/MELISSA_LEFT.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 12.1f), (player.collider.height));
			player.characters.animsRIGTH[7] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[7] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);

			rescale = LoadImage("assets/KICK_MELISSA.png");
			ImageResize(&rescale, ((player.collider.width + 50) * 12), (player.collider.height));
			player.characters.animsRIGTH[8] = LoadTextureFromImage(rescale);
			ImageFlipHorizontal(&rescale);
			player.characters.animsLEFT[8] = LoadTextureFromImage(rescale);
			UnloadImage(rescale);
		}

		rescale = LoadImage("assets/HEALTH_BAR.png");
		ImageResize(&rescale, screenWidht / 2.5, 70);
		if (player.direction.x == 0)
			ImageFlipHorizontal(&rescale);
		player.LIFE_BAR = LoadTextureFromImage(rescale);
		UnloadImage(rescale);
	}

	void UnloadTextures(Pjs& player) {
		UnloadTexture(player.characters.animsRIGTH[0]);
		UnloadTexture(player.characters.animsRIGTH[1]);
		UnloadTexture(player.characters.animsRIGTH[2]);
		UnloadTexture(player.characters.animsRIGTH[3]);
		UnloadTexture(player.characters.animsRIGTH[4]);
		UnloadTexture(player.characters.animsRIGTH[5]);
		UnloadTexture(player.characters.animsRIGTH[6]);
		UnloadTexture(player.characters.animsRIGTH[7]);
		UnloadTexture(player.characters.animsRIGTH[8]);

		UnloadTexture(player.characters.animsLEFT[0]);
		UnloadTexture(player.characters.animsLEFT[1]);
		UnloadTexture(player.characters.animsLEFT[2]);
		UnloadTexture(player.characters.animsLEFT[3]);
		UnloadTexture(player.characters.animsLEFT[4]);
		UnloadTexture(player.characters.animsLEFT[5]);
		UnloadTexture(player.characters.animsLEFT[6]);
		UnloadTexture(player.characters.animsLEFT[7]);
		UnloadTexture(player.characters.animsLEFT[8]);

		UnloadTexture(player.CH_MARC_LIFEBAR);
		UnloadTexture(player.LIFE_BAR);
	}

	void CalcFrameAnimPlayers(Pjs& player) {

		if (player.state.STATE_IDLE) {
			player.characters.framesSpeed = 8;
		}
		if (player.state.STATE_PUNCH) {
			player.characters.framesSpeed = 8;
			if (player.characters.champ == Melissa) {
				player.characters.framesSpeed = 12;
			}
		}
		if (player.state.STATE_KICK) {
			player.characters.framesSpeed = 8;
		}
		if (player.state.STATE_JUMP) {
			player.characters.framesSpeed = 5;
		}
		if (player.state.STATE_RIGHTW) {
			player.characters.framesSpeed = 7;
		}
		if (player.state.STATE_LEFTW) {
			player.characters.framesSpeed = 7;
		}
		if (player.state.STATE_BLOCK) {
			player.characters.framesSpeed = 6;
		}

		player.characters.framesCounter++;
		if (player.characters.framesCounter >= (120 / player.characters.framesSpeed))
		{
			player.characters.framesCounter = 0;
			player.characters.currentFrame++;

			if (player.characters.currentFrame > player.characters.framesAnim) player.characters.currentFrame = 0;

			player.frameRec.x = ((float)player.characters.currentFrame) * ((float)player.characters.animsRIGTH[0].width / player.characters.framesAnim);
		}
		if (player.characters.framesSpeed > MAX_FRAME_SPEED) { player.characters.framesSpeed = MAX_FRAME_SPEED; }
		else if (player.characters.framesSpeed < MIN_FRAME_SPEED) { player.characters.framesSpeed = MIN_FRAME_SPEED; }
	}

	void DrawPlayers(Pjs& player) {
		DrawRectangleLinesEx(player.collider, 2, GREEN);
		DrawRectangleLinesEx(player.characters.colliders[2], 2, VIOLET);
		DrawRectangleLinesEx(player.characters.colliders[0], 2, YELLOW);
		Vector2 auxPj2;
		auxPj2 = { playerDummy.Pos.x + player.collider.width , playerDummy.Pos.y };
		DrawLineEx(player1.Pos, auxPj2, 3, RED);

		//HEALTH BARS
		DrawRectangleRec(player1.LIFE, RED);
		DrawRectangleRec(playerDummy.LIFE, RED);

		DrawTexture(player1.CH_MARC_LIFEBAR, 0, 0, WHITE);
		DrawTexture(playerDummy.CH_MARC_LIFEBAR, screenWidht - playerDummy.CH_MARC_LIFEBAR.width, 0, WHITE);
		DrawTexture(player1.LIFE_BAR, player1.CH_MARC_LIFEBAR.width, 0, WHITE);
		DrawTexture(playerDummy.LIFE_BAR, ((screenWidht / 2) + 5), 0, WHITE);

		//DETERMINAR LADO DE TEXTURA con VEC2 DIRECTION  1 --> Derecha 0 --> Izquierda
		if (player1.Pos.x < playerDummy.Pos.x) {
			player1.direction.x = 1;
			playerDummy.direction.x = 0;
		}
		else {
			player1.direction.x = 0;
			playerDummy.direction.x = 1;
		}

		//DrawLineEx(playerDummy.Pos, player1.Pos, 3, PURPLE);

		if (player.state.STATE_IDLE) {
			if(player.direction.x == 1)
				DrawTextureRec(player.characters.animsRIGTH[0], player.frameRec, player.Pos, WHITE);
			else
				DrawTextureRec(player.characters.animsLEFT[0], player.frameRec, player.Pos, WHITE);
		}
		if (player.state.STATE_CROUCH) {
			if (!player.state.STATE_BLOCK_CROUCH) {
					if(player.direction.x == 1)
						DrawTextureRec(player.characters.animsRIGTH[1], player.frameRec, player.Pos, WHITE);
					else
						DrawTextureRec(player.characters.animsLEFT[1], player.frameRec, player.Pos, WHITE);
			}
			else {
				if (player.direction.x == 1) {
					DrawTextureRec(player.characters.animsRIGTH[5], player.frameRec, player.Pos, WHITE);
					DrawRectangleLinesEx(player.characters.colliders[1], 2, WHITE);
				}
				else {
					DrawTextureRec(player.characters.animsLEFT[5], player.frameRec, player.Pos, WHITE);
					//DrawRectangleLinesEx(player.characters.colliders[1], 2, WHITE);
					//HAY QUE INVERTIR EL COLLIDER
				}
			}
		}
		if (player.state.STATE_RIGHTW) {
			if(player.direction.x == 1)
				DrawTextureRec(player.characters.animsRIGTH[2], player.frameRec, player.Pos, WHITE);
			else
				DrawTextureRec(player.characters.animsLEFT[2], player.frameRec, player.Pos, WHITE);
		}
		if (player.state.STATE_JUMP) {
			if(player.direction.x == 1)
				DrawTextureRec(player.characters.animsRIGTH[3], player.frameRec, player.Pos, WHITE);
			else
				DrawTextureRec(player.characters.animsLEFT[3], player.frameRec, player.Pos, WHITE);
		}
		if (player.state.STATE_BLOCK && !player.state.STATE_CROUCH) {
			if (player.direction.x == 1) {
				DrawTextureRec(player.characters.animsRIGTH[4], player.frameRec, player.Pos, WHITE);
				DrawRectangleLinesEx(player.characters.colliders[1], 2, WHITE);
			}
			else {
				DrawTextureRec(player.characters.animsLEFT[4], player.frameRec, player.Pos, WHITE);
				//DrawRectangleLinesEx(player.characters.colliders[1], 2, WHITE);
				//HAY QUE INVERTIR BOX COLLIDER
			}
		}
		if (player.state.STATE_PUNCH) {
			if (!player.state.STATE_EXIT_P) {
				if(player.direction.x == 1)
					DrawTextureRec(player.characters.animsRIGTH[6], player.frameRec, player.Pos, WHITE);
				else
					DrawTextureRec(player.characters.animsLEFT[6], player.frameRec, player.Pos, WHITE);

				//MODIFICAR COLLIDER (INVERTIRLO) EN SUS FUNCIONES DE INPUT
			}
		}
		if (player.state.STATE_LEFTW) {
			if(player.direction.x == 1)
				DrawTextureRec(player.characters.animsRIGTH[7], player.frameRec, player.Pos, WHITE);
			else
				DrawTextureRec(player.characters.animsLEFT[7], player.frameRec, player.Pos, WHITE);
		}
		if (player.state.STATE_KICK) {
			if(player.direction.x == 1)
				DrawTextureRec(player.characters.animsRIGTH[8], player.frameRec, player.Pos, WHITE);
			else
				DrawTextureRec(player.characters.animsLEFT[8], player.frameRec, player.Pos, WHITE);

			//INVERTIR BOX COLLIDER EN INPUTS PLAYERS
		}

		//DrawRectangleLinesEx(player1.frameRec, 2, RED);
	}

	void CalcDeltaTime() {
		PREVIUS_TIME = CURRENT_TIME;
		CURRENT_TIME = (float)GetTime();
		DELTA_TIME = CURRENT_TIME - PREVIUS_TIME;
		if (DELTA_TIME > 0.15f)
			DELTA_TIME = 0.15f;
	}

	void PhysicsPlayers(Pjs& firstPj, Pjs& secondPj) {

		//GRAVEDAD EN ACCION
		if (!firstPj.inFloor) {
			firstPj.collider.y = firstPj.collider.y + firstPj.speed.y * DELTA_TIME;
			firstPj.speed.y = firstPj.speed.y - firstPj.gravity.y * (DELTA_TIME * 2);
			firstPj.state.STATE_RIGHTW = false;
			firstPj.state.STATE_LEFTW = false;
			firstPj.state.STATE_BLOCK = false;
			firstPj.state.STATE_CROUCH = false;
			firstPj.state.STATE_PUNCH = false;
		}
		else {
			firstPj.speed = {400.0f,20.0f};
			firstPj.collider.x = firstPj.collider.x;
			firstPj.collider.y = firstPj.collider.y;
			firstPj.state.STATE_JUMP = false;
		}

		if (!secondPj.inFloor) {
			secondPj.collider.y = secondPj.collider.y + secondPj.speed.y * DELTA_TIME;
			secondPj.speed.y = secondPj.speed.y - secondPj.gravity.y * (DELTA_TIME * 2);
			secondPj.state.STATE_RIGHTW = false;
			secondPj.state.STATE_LEFTW = false;
			secondPj.state.STATE_BLOCK = false;
			secondPj.state.STATE_CROUCH = false;
			secondPj.state.STATE_PUNCH = false;
		}
		else {
			secondPj.speed = { 400.0f,20.0f };
			secondPj.collider.x = secondPj.collider.x;
			secondPj.collider.y = secondPj.collider.y;
			secondPj.state.STATE_JUMP = false;
		}
		firstPj.Pos = { firstPj.collider.x,firstPj.collider.y };
		secondPj.Pos = { secondPj.collider.x,secondPj.collider.y };
	}

	void CheckOnFloor(Pjs& player) {
		if (CheckCollisionRecs(player.collider, Stage::scenario.floor))
			player.inFloor = true;
		else
			player.inFloor = false;
	}

	//PRIMARY INPUT (PJ1)

	void InputsPlayer1(Pjs& player1) {

		//SALTO BEGIN
		if (player1.inFloor){
			if (IsKeyDown(KEY_SPACE)) {
				player1.state.STATE_JUMP = true;
				if (player1.state.STATE_JUMP && player1.inFloor) {
					player1.characters.currentFrame = 8;
				}
			}
			if (!player1.state.STATE_PUNCH && !player1.state.STATE_CROUCH && !player1.state.STATE_BLOCK && !player1.state.STATE_JUMP && !player1.state.STATE_KICK && !player1.state.STATE_LEFTW && !player1.state.STATE_RIGHTW) {
				player1.state.STATE_IDLE = true;
				player1.frameRec.width = (float)(player1.characters.animsRIGTH[0].width / 8);

				player1.characters.framesAnim = 8;
			}
			else {
				player1.state.STATE_IDLE = false;
			}
		}
		
		//SALTO IN ACTION
		if (player1.state.STATE_JUMP) {
			player1.characters.framesAnim = 8;
			player1.collider.y -= (player1.maxHeightJump * DELTA_TIME) * 8;
			player1.collider.height = 250;
			if (player1.characters.currentFrame == 6) {
				player1.collider.height = 340;
				player1.collider.y = Stage::scenario.floor.y - 340;
			}
		}

		//CROUCH BEGIN
		if (IsKeyDown(KEY_S)) {
			if (player1.inFloor) {
				player1.state.STATE_CROUCH = true;
				player1.state.STATE_EXIT_C = false;
				player1.characters.framesAnim = 2;

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
		if (player1.inFloor) {
			if (player1.state.STATE_CROUCH) {
				player1.collider.height = 190;
				player1.frameRec.height = 190;
				player1.frameRec.width = (float)(player1.characters.animsRIGTH[1].width / 4);
				if(player1.inFloor)
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
					if (player1.inFloor) {
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

		if (!player1.state.STATE_BLOCK && !player1.state.STATE_KICK && !player1.state.STATE_PUNCH) {
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
			player1.collider.x -= (player1.speed.x * DELTA_TIME);
			if (player1.inFloor) {
				player1.characters.framesAnim = 4;

				if (player1.inFloor) {
					player1.characters.framesAnim = 4;
				}
			}
		}

		if (player1.state.STATE_RIGHTW) {
			player1.collider.x += (player1.speed.x * DELTA_TIME);
			if (player1.inFloor) {
				player1.characters.framesAnim = 4;

				if (player1.inFloor) {
					player1.characters.framesAnim = 4;
				}
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

		if (player1.inFloor) {
			if (player1.state.STATE_BLOCK) {
				player1.characters.framesAnim = 8;
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
				if (player1.inFloor) {
					player1.characters.framesAnim = 6;
					player1.characters.currentFrame = 0;

					if (player1.characters.champ == Jack || player1.characters.champ == Valhim) {
						player1.frameRec.width += player1.frameRec.width - 100;
					}
					else {
						player1.frameRec.width += player1.frameRec.width - 120;
					}
					
					player1.state.STATE_PUNCH = true;
					player1.state.STATE_EXIT_P = false;
				}
			}
		}

		if (player1.inFloor) {
			if (player1.state.STATE_PUNCH) {
				player1.characters.colliders[0].x = (player1.collider.x - 40) + player1.characters.colliders[0].width;
				if (player1.characters.currentFrame == 6)
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
			if (player1.inFloor) {
				player1.characters.framesAnim = 6;
				player1.characters.currentFrame = 0;

				if (player1.characters.champ == Valhim) {
					player1.frameRec.width += player1.frameRec.width - 100;
				}
				else {
					player1.frameRec.width += player1.frameRec.width - 120;
				}

				player1.state.STATE_KICK = true;
				player1.state.STATE_EXIT_K = false;
			}
		}

		if (player1.inFloor) {
			if (player1.state.STATE_KICK) {
				player1.characters.colliders[2].x = (player1.collider.x - punchLeght) + player1.characters.colliders[2].width;
				if(player1.characters.currentFrame == 6)
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

	//SECONDARY INPUT (PJ2)

	void InputsPlayer2(Pjs& player2) {

		//SALTO BEGIN
		if (player2.inFloor) {
			if (IsKeyDown(KEY_UP)) {
				player2.state.STATE_JUMP = true;
				if (player2.state.STATE_JUMP && player2.inFloor) {
					player2.characters.currentFrame = 8;
				}
			}
			if (!player2.state.STATE_PUNCH && !player2.state.STATE_CROUCH && !player2.state.STATE_BLOCK && !player2.state.STATE_JUMP && !player2.state.STATE_KICK && !player2.state.STATE_LEFTW && !player2.state.STATE_RIGHTW) {
				player2.state.STATE_IDLE = true;
				player2.frameRec.width = (float)(player2.characters.animsRIGTH[0].width / 8);

				player2.characters.framesAnim = 8;
			}
			else {
				player2.state.STATE_IDLE = false;
			}
		}

		//SALTO IN ACTION
		if (player2.state.STATE_JUMP) {
			player2.characters.framesAnim = 8;
			player2.collider.y -= (player2.maxHeightJump * DELTA_TIME) * 8;
			player2.collider.height = 250;
			if (player2.characters.currentFrame == 6) {
				player2.collider.height = 340;
				player2.collider.y = Stage::scenario.floor.y - 340;
			}
		}

		//CROUCH BEGIN
		if (IsKeyDown(KEY_DOWN)) {
			if (player2.inFloor) {
				player2.state.STATE_CROUCH = true;
				player2.state.STATE_EXIT_C = false;
				player2.characters.framesAnim = 2;

				if (IsKeyDown(KEY_KP_3)) {
					player2.state.STATE_BLOCK_CROUCH = true;
				}
				else {
					player2.state.STATE_BLOCK_CROUCH = false;
				}
			}
		}
		else
			player2.state.STATE_CROUCH = false;

		//CROUCH IN ACTION
		if (player2.inFloor) {
			if (player2.state.STATE_CROUCH) {
				player2.collider.height = 190;
				player2.frameRec.height = 190;
				player2.frameRec.width = (float)(player2.characters.animsRIGTH[1].width / 4);
				if (player2.inFloor)
					player2.collider.y = 470;

				if (player2.state.STATE_BLOCK_CROUCH) {
					player2.characters.colliders[1].x = player2.collider.x + (player2.collider.width - 70);
				}
				else {
					player2.characters.colliders[1].x = player2.collider.x;
					player2.characters.colliders[1].y = player2.collider.y;
				}
			}
			else {
				if (!player2.state.STATE_CROUCH && !player2.state.STATE_EXIT_C) {
					if (player2.inFloor) {
						player2.collider.y = Stage::scenario.floor.y - 340;
					}
					else {
						player2.collider.y = player2.collider.y;
					}
					player2.state.STATE_EXIT_C = true;
				}
				player2.collider.height = 340;
				player2.frameRec.height = 340;
			}
		}

		//MOVE SIDES

		if (!player2.state.STATE_BLOCK && !player2.state.STATE_KICK && !player2.state.STATE_PUNCH) {
			if (IsKeyDown(KEY_RIGHT)) {
				player2.state.STATE_RIGHTW = true;
				player2.state.STATE_PUNCH = false;
			}
			else {
				player2.state.STATE_RIGHTW = false;
			}
			if (IsKeyDown(KEY_LEFT)) {
				player2.state.STATE_LEFTW = true;
				player2.state.STATE_PUNCH = false;
			}
			else {
				player2.state.STATE_LEFTW = false;
			}
		}

		if (player2.state.STATE_LEFTW) {
			player2.collider.x -= (player2.speed.x * DELTA_TIME);
			if (player2.inFloor) {
				player2.characters.framesAnim = 4;
			}
		}

		if (player2.state.STATE_RIGHTW) {
			player2.collider.x += (player2.speed.x * DELTA_TIME);
			if (player2.inFloor) {
				player2.characters.framesAnim = 4;
			}
		}

		//BLOCK DAMAGE

		if (!player2.state.STATE_LEFTW && !player2.state.STATE_RIGHTW) {
			if (IsKeyDown(KEY_KP_3)) {
				player2.state.STATE_BLOCK = true;
				player2.state.STATE_EXIT_B = false;
			}
			else {
				player2.state.STATE_BLOCK = false;
			}
		}

		if (player2.inFloor) {
			if (player2.state.STATE_BLOCK) {
				player2.characters.framesAnim = 8;
				player2.characters.colliders[1].x = player2.collider.x + (player2.collider.width - 70);
			}
			else {
				if (!player2.state.STATE_BLOCK && !player2.state.STATE_EXIT_B) {
					player2.state.STATE_EXIT_B = true;
				}
				player2.characters.colliders[1].x = player2.collider.x;
				player2.characters.colliders[1].y = player2.collider.y;
			}
		}

		//PUNCH
		if (!player2.state.STATE_LEFTW && !player2.state.STATE_RIGHTW && !player2.state.STATE_BLOCK && !player2.state.STATE_JUMP && !player2.state.STATE_CROUCH) {
			if (IsKeyPressed(KEY_KP_1)) {
				if (player2.inFloor) {
					player2.characters.framesAnim = 6;
					player2.characters.currentFrame = 0;

					if (player2.characters.champ == Jack || player2.characters.champ == Valhim) {
						player2.frameRec.width += player2.frameRec.width - 100;
					}
					else {
						player2.frameRec.width += player2.frameRec.width - 120;
					}

					player2.state.STATE_PUNCH = true;
					player2.state.STATE_EXIT_P = false;
				}
			}
		}

		if (player2.inFloor) {
			if (player2.state.STATE_PUNCH) {
				player2.characters.colliders[0].x = (player2.collider.x - 40) + player2.characters.colliders[0].width;
				if (player2.characters.currentFrame == 6)
					player2.state.STATE_PUNCH = false;
			}
			else {
				if (!player2.state.STATE_PUNCH && !player2.state.STATE_EXIT_P) {
					player2.state.STATE_EXIT_P = true;
				}
				player2.characters.colliders[0] = { player2.collider.x, player2.collider.y + 50, punchLeght, punchHeight };
			}
		}

		//KICK

		//if (!player1.state.STATE_LEFTW && !player1.state.STATE_RIGHTW && !player1.state.STATE_BLOCK && !player1.state.STATE_JUMP && !player1.state.STATE_CROUCH && player1.state.STATE_PUNCH) {
		//}
		if (IsKeyPressed(KEY_KP_2)) {
			if (player2.inFloor) {
				player2.characters.framesAnim = 6;
				player2.characters.currentFrame = 0;

				if (player2.characters.champ == Valhim) {
					player2.frameRec.width += player2.frameRec.width - 100;
				}
				else {
					player2.frameRec.width += player2.frameRec.width - 120;
				}

				player2.state.STATE_KICK = true;
				player2.state.STATE_EXIT_K = false;
			}
		}

		if (player2.inFloor) {
			if (player2.state.STATE_KICK) {
				player2.characters.colliders[2].x = (player2.collider.x - punchLeght) + player2.characters.colliders[2].width;
				if (player2.characters.currentFrame == 6)
					player2.state.STATE_KICK = false;
			}
			else {
				if (!player2.state.STATE_KICK && !player2.state.STATE_EXIT_K) {
					player2.state.STATE_EXIT_K = true;
				}
				player2.characters.colliders[2] = { player2.collider.x - (kickLenght / 2), player2.collider.y + 110, kickLenght, kickHeight };
			}
		}

	}

}