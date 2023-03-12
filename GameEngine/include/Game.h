
#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <vector>
using namespace std;

class AssetManager;
class ColliderComponent;
class Game
{
public:
    Game();
    ~Game();

    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    bool running(){return isRunning;}
    void clean();

    void addPoint(){point++;};
    void setPoint(int p){point = p;};
    int getPoint(){return point;};
    
    
    static SDL_Renderer *renderer;
    static SDL_Event event;
    static bool isRunning;
    static SDL_Rect camera;
    static AssetManager* assets;

    enum groupLabels : size_t
{ // maxstorlek 32 grupper.
    groupMap,
    groupPlayers,
    groupColliders,
    groupProjectiles,
    groupPointNests

};


private:

    int numb = 0;
    int count = 0;
    int point = 0;

    
    SDL_Window *window;
};

#endif //Game_h