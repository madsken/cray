#include "raylib.h"

int main(int argc, char *argv[]) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "cray");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("CRAY CRAY YOOO", 190, 200, 20, LIGHTGRAY);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
