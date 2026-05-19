#include "game.h"
#include <raylib.h>

void InitGame(GameState *state) { state->counter = 0; }

void UpdateGame(GameState *state) { state->counter++; }

void DrawGame(GameState *state) {
  DrawText(TextFormat("Counter: %d", state->counter), 20, 20, 20, DARKGRAY);
}
