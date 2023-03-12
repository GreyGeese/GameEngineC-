#include "AssetManager.h"
#include "ECS/Components.h"
AssetManager::AssetManager(Manager* man): manager(man){}

AssetManager::~AssetManager(){}

void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, string id){
    auto& projectile(manager->addEntity());
    projectile.addComponent<TransformComponent>(pos.x,pos.y,32,32,3);
    projectile.addComponent<SpriteComponent>(id,true);
    projectile.addComponent<ProjectileComponent>(range, speed,vel);
    projectile.addComponent<ColliderComponent>("projectile");
    projectile.addGroup(Game::groupProjectiles);
}
void AssetManager::CreatePointNest(Vector2D pos, string id){

    auto& pointNest(manager->addEntity());
    pointNest.addComponent<TransformComponent>(pos.x,pos.y,32,32,1);
    pointNest.addComponent<SpriteComponent>(id,false);
    pointNest.addComponent<ColliderComponent>("pointNest");
    pointNest.addGroup(Game::groupPointNests);
}


void AssetManager::AddTexture(string id, const char* path){
 textures.emplace(id,TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(string id){
    return textures[id];
}