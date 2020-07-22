#include "gameLoop.h"

namespace GL {

	void InitializeAll(){

		InitializeScreen();

	}

	void Loop() {
		
		InitializeAll();
		
		while (!WindowShouldClose()){

			ClearBackground(BLACK);

			BeginDrawing();

			if (IsKeyPressed(KEY_ESCAPE))
				WindowShouldClose();

			EndDrawing();
		}

		CloseWindow();
	}
}