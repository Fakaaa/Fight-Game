#ifndef PLAYERS
#define PLAYERS
#include "raylib.h"

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
		Rectangle colliders[5];
	};

	struct PlayerState
	{
		bool STATE_JUMP;
		//float AIR_TIME;
		bool STATE_PUNCH;
		bool STATE_CROUCH;
		bool STATE_EXIT;
		bool STATE_KICK;
		bool STATE_BLOCK;
	};

	struct Pjs {
		Rectangle collider;
		int champSelected;
		Champions characters;
		Vector2 direction;
		Vector2 speed;
		Vector2 gravity;
		float maxHeightJump;
		PlayerState state;
	};

	extern Pjs player1;
	extern bool inFloor;

	extern float PREVIUS_TIME;
	extern float CURRENT_TIME;
	extern float DELTA_TIME;

	extern void InitializePlayers();
	extern void DrawPlayers();
	extern void LoadTextures();
	extern void UnloadTextures();
	extern void InputsPlayer();
	extern void PhysicsPlayers();
	extern void CheckOnFloor();
	extern void CalcDeltaTime();
}
#endif // !PLAYERS