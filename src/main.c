#include "game.h"
#include "raylib.h"

#include <dlfcn.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

typedef void (*InitGameFn)(GameState *);
typedef void (*UpdateGameFn)(GameState *);
typedef void (*DrawGameFn)(GameState *);

typedef struct {
  void *handle;
  InitGameFn InitGame;
  UpdateGameFn UpdateGame;
  DrawGameFn DrawGame;
  time_t lastWriteTime;
} GameLib;

static time_t GetFileTime(const char *path) {
  struct stat attr;
  stat(path, &attr);
  return attr.st_mtime;
}

void UnloadGame(GameLib *lib) {
  if (lib->handle) {
    dlclose(lib->handle);
    lib->handle = NULL;
  }
}

static int LoadGame(GameLib *lib, const char *path) {
  printf("Unloading game\n");
  UnloadGame(lib);

  printf("dlclose\n");
  if (lib->handle)
    dlclose(lib->handle);

  printf("dlopen game\n");
  lib->handle = dlopen(path, RTLD_NOW);
  if (!lib->handle) {
    printf("dlopen error: %s\n", dlerror());
    return 0;
  }

  printf("set init game\n");
  lib->InitGame = (InitGameFn)dlsym(lib->handle, "InitGame");
  printf("set update game\n");
  lib->UpdateGame = (UpdateGameFn)dlsym(lib->handle, "UpdateGame");
  printf("set draw game\n");
  lib->DrawGame = (DrawGameFn)dlsym(lib->handle, "DrawGame");

  printf("set last write game\n");
  lib->lastWriteTime = GetFileTime(path);
  return 1;
}

int main(void) {
  InitWindow(800, 450, "Cray - Hot Reload");

  const char *libPath = "./libgame.so";

  GameLib gameLib = {0};
  GameState gameState = {0};

  LoadGame(&gameLib, libPath);
  gameLib.InitGame(&gameState);

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // Hot Reload check
    time_t newTime = GetFileTime(libPath);
    if (newTime != gameLib.lastWriteTime) {
      printf("Reloading game...\n");
      LoadGame(&gameLib, libPath);
      printf("Done reloading game...");
      gameLib.InitGame(&gameState);
    }

    gameLib.UpdateGame(&gameState);

    BeginDrawing();
    ClearBackground(RAYWHITE);

    gameLib.DrawGame(&gameState);

    EndDrawing();
  }

  CloseWindow();

  if (gameLib.handle) {
    dlclose(gameLib.handle);
  }

  return 0;
}
