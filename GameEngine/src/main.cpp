#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include "Game.h"

#define SCREEN_WIDTH 800 //ska gå att dela med 32 då så
#define SCEEN_HEIGHT 640 //att måtten stämmer  med tilemap system.

Game *game = nullptr;
int main(int argc, char *argv[])
{

  //framerate cappar
  const int FPS = 60;
  const int frameDelay = 1000 / FPS;
  Uint32 frameStart;
  int frameTime;
  //_________________

  //SKAPAR SPEL
  game = new Game();
  game->init("SeagulEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCEEN_HEIGHT, false);

  while (game->running())
  {

    frameStart = SDL_GetTicks();
    game->handleEvents();
    game->update();
    game->render();
    frameTime = SDL_GetTicks() - frameStart; //tiden mellan början och slutet på en frame.

    if (frameDelay > frameTime)
    {                                    // ifall frameDelay är störe än frameTime
      SDL_Delay(frameDelay - frameTime); //minska antalet frames till 60
    }
  }
  game->clean();

  return 0;
}