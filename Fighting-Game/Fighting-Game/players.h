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

	struct Pjs {
		Rectangle collider;
		int champSelected;
		Champions characters;
		Vector2 direction;
	};

	extern void InitializePlayers();
	extern void DrawPlayers();
	extern void LoadTextures();
	extern void UnloadTextures();
}
#endif // !PLAYERS