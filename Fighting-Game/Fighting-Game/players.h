#ifndef PLAYERS
#define PLAYERS
#include "raylib.h"

#define MAX_FRAME_SPEED 15
#define MIN_FRAME_SPEED 1

namespace Players {

	enum ChampionID {
		Jack,
		Jhon,
		Melissa,
		Anna
	};

	struct Champions{
		ChampionID champ;
		Texture2D anims[9];
		Rectangle colliders[2];
	};

	struct PlayerState{
		bool STATE_JUMP;

		bool STATE_PUNCH;
		bool STATE_EXIT_P;

		bool STATE_CROUCH;
		bool STATE_EXIT_C;

		bool STATE_KICK;
		bool STATE_EXIT_K;

		bool STATE_BLOCK;
		bool STATE_EXIT_B;

		bool STATE_IDLE;
		bool STATE_LEFTW;
		bool STATE_RIGHTW;
	};

	struct Pjs {
		Rectangle collider;
		Vector2 Pos;
		Rectangle frameRec;
		int champSelected;
		Champions characters;
		Vector2 direction;
		Vector2 speed;
		Vector2 gravity;
		float maxHeightJump;
		PlayerState state;
	};

	extern Pjs player1;
	extern Pjs playerDummy;
	extern int framesAnim;
	extern bool inFloor;
	extern int currentFrame;
	extern int framesCounter;
	extern int framesSpeed;

	extern float PREVIUS_TIME;
	extern float CURRENT_TIME;
	extern float DELTA_TIME;

	extern void InitializePlayers();
	extern void CalcFrameAnimPlayer1();
	extern void DrawPlayers();
	extern void LoadTextures();
	extern void UnloadTextures();
	extern void InputsPlayer();
	extern void PhysicsPlayers();
	extern void CheckOnFloor();
	extern void CalcDeltaTime();
}
#endif // !PLAYERS