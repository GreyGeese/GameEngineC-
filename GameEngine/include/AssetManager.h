#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS/ECS.h"
using namespace std;
// Vad detta gör: skapar textures. Bygger gameobjects.
class AssetManager{
public:
    AssetManager(Manager* man); 
    ~AssetManager();
    //gameobjects
    void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, string id);

    void CreatePointNest(Vector2D pos, string id);

    //TextureManagement
    void AddTexture(string id, const char* path);
    SDL_Texture* GetTexture(string id);
private:
    Manager* manager;
    map<string, SDL_Texture*> textures;


};




#endif