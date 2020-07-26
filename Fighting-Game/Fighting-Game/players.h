#ifndef PLAYERS
#define PLAYERS
#include "raylib.h"

#define MAX_FRAME_SPEED 15
#define MIN_FRAME_SPEED 1

namespace Players {

	enum ChampionID {
		Jack,
		Valhim,
		Melissa,
		Anna
	};

	struct Champions{
		ChampionID champ;
		Texture2D animsRIGTH[9];
		Texture2D animsLEFT[9];
		Rectangle colliders[3];
		int framesAnim;
		int currentFrame;
		int framesCounter;
		int framesSpeed;
	};

	struct PlayerState{
		bool STATE_JUMP;

		bool STATE_PUNCH;
		bool STATE_PUNCH_CROUCH;
		bool STATE_EXIT_P;

		bool STATE_CROUCH;
		bool STATE_EXIT_C;

		bool STATE_KICK;
		bool STATE_KICK_CROUCH;
		bool STATE_EXIT_K;

		bool STATE_BLOCK;
		bool STATE_BLOCK_CROUCH;
		bool STATE_EXIT_B;

		bool STATE_IDLE;
		bool STATE_LEFTW;
		bool STATE_RIGHTW;
	};

	struct Pjs {
		Rectangle collider;
		Vector2 Pos;
		Rectangle frameRec;
		ChampionID champSelected;
		float HP;
		Texture2D LIFE_BAR;
		Rectangle LIFE;
		Champions characters;
		Vector2 direction;
		Vector2 speed;
		Vector2 gravity;
		float maxHeightJump;
		float maxDashDistance;
		PlayerState state;
		bool inFloor;
	};

	extern Pjs player1;
	extern Pjs playerDummy;

	extern float punchLeght;
	extern float punchHeight;
	extern float blockSize;
	extern float kickLenght;
	extern float kickHeight;

	extern float PREVIUS_TIME;
	extern float CURRENT_TIME;
	extern float DELTA_TIME;

	extern void InitializePlayers();
	extern void CalcFrameAnimPlayers(Pjs& player);
	extern void DrawPlayers(Pjs& player);
	extern void LoadTextures(Pjs& player);
	extern void UnloadTextures(Pjs& player);
	extern void InputsPlayer1(Pjs& player1);
	extern void InputsPlayer2(Pjs& player2);
	extern void PhysicsPlayers(Pjs& firstPj, Pjs& secondPj);
	extern void CheckOnFloor(Pjs& player);
	extern void CalcDeltaTime();
}
#endif // !PLAYERS