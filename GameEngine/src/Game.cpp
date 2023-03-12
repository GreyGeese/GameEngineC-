#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
using namespace std;

Map *maps;
Manager manager;
SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, 1600, 1280};
AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

 // skapar ett nytt gameobject med namnet player.
auto& player(manager.addEntity());

Game::Game() {}

Game::~Game() {}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 135, 206, 250, 255);
        }

        isRunning = true;
    }
    assets->AddTexture("terrain","assets/terrain_ss.png" );
    assets->AddTexture("player","assets/SeagulPlayer.png" );
    assets->AddTexture("projectile","assets/EagleEnemy.png");
    assets->AddTexture("pointNest", "assets/proj.png");

    maps = new Map("terrain", 3,32); // skala tilesize
    //ECS implementation
    maps->LoadMap("assets/map.map", 25, 20);     //25,20 = antalet siffror som finns i mappen X,Y kordinat.

    player.addComponent<TransformComponent>(4); //(10) = spelarens sprite storlek x 10.
    player.addComponent<SpriteComponent>("player",true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);

    assets->CreatePointNest(Vector2D(400,350), "pointNest");
}
auto &tiles(manager.getGroup(Game::groupMap));
auto &players(manager.getGroup(Game::groupPlayers));
auto &projectiles(manager.getGroup(Game::groupProjectiles));
auto &pointNests(manager.getGroup(Game::groupPointNests));
auto &colliders(manager.getGroup(Game::groupColliders));
void Game::handleEvents()
{
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;

    default:
        break;
    }
}

void Game::update()
{
    // gör om alla randoms så det är tydligare vad de betyder. Oklart i nuläget.
    //random = random spawn points %1400 för det är map sizen minus colliders så den inte hamnar 
    //utanför delar av mappen man inte kan ta sig till med marginal.
    
    
    // spawnar projectiles----------------------------------------------------
    //borde göras om snyggare. men funkar för nu
    if(numb == 1){
        // gör så att spriteflip funkar på projektilerna.
        
        assets->CreateProjectile(Vector2D(camera.x+(rand()%10),camera.y+(rand()%800)),Vector2D(2,0), 200, 2, "projectile"); //horizontell
        assets->CreateProjectile(Vector2D(camera.x+(rand()%10),camera.y+(rand()%800)),Vector2D(2,0), 200, 2, "projectile");
        assets->CreateProjectile(Vector2D(camera.x+(rand()%800),camera.y+(rand()%10)),Vector2D(0,2), 200, 2, "projectile"); //vertikal
        assets->CreateProjectile(Vector2D(camera.x+(rand()%800),camera.y+(rand()%10)),Vector2D(0,2), 200, 2, "projectile");
    }
    if(numb !=100){
        numb++;
    }
    if(numb == 100){
        numb = 0;
    }
    //------------------------------------------------------------------------

    SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = player.getComponent<TransformComponent>().position;
    manager.refresh();
    manager.update();

    // gör så att spelaren inte kan gå utanför mappen ------------------------
    for(auto& c :colliders){
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        if(Collision::AABB(cCol,playerCol)){
            player.getComponent<TransformComponent>().position = playerPos;
        }

    }
    //------------------------------------------------------------------------
    for(auto& p : projectiles){
        if(Collision::AABB(player.getComponent<ColliderComponent>().collider,
        p->getComponent<ColliderComponent>().collider)){
            cout<< "U lost"<<endl;
            Game::setPoint(0);
            cout<< Game::getPoint()<< endl;
            
            p->destroy();
        }   
         
    }
    
    //spawnar nytt pointNest när förra är taget -------------------------------
    for(auto& n : pointNests){
        if(Collision::AABB(player.getComponent<ColliderComponent>().collider,
        n->getComponent<ColliderComponent>().collider)){
            n->destroy();

            // gör rand() till en egen klass eller nåt det där ser inte snyggt ut.
            assets->CreatePointNest(Vector2D(150+(rand()%1400),150+(rand()%1000)), "pointNest");
            Game::addPoint();
            cout << "points: "<< Game::getPoint()<< endl;

        }
    }
    //--------------------------------------------------------------------------


    camera.x = player.getComponent<TransformComponent>().position.x - 400;
    camera.y = player.getComponent<TransformComponent>().position.y - 320;

    if (camera.x < 0)
        camera.x = 0;
    if (camera.y < 0)
        camera.y = 0;
    if (camera.x > camera.w)
        camera.x = camera.w;
    if (camera.y > camera.h)
        camera.y = camera.h;
}

void Game::render()
{
    SDL_RenderClear(renderer); // längst upp renderas längst bak.

    for (auto &t : tiles)
    {
        t->draw();
    }
     for (auto &c : colliders)
    {
        c->draw();
    }
    
    for (auto &p : players)
    {
        p->draw();
    }
    for (auto &p : projectiles)
    {
        p->draw();
    }
     for (auto &n : pointNests)
    {
        n->draw();
    }
   
   
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "gameCleaned" << endl;
}

