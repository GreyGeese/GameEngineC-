#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "Components.h"
#include "SDL2/SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>
#include "../AssetManager.h"


class SpriteComponent : public Component
{

private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

    bool animated = false;
    int frames = 0;
    int speed = 100; //fördröjning mellan frames i millisekunder
public:
    
    int animIndex = 0;
    map<string, Animation> animations; 
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
    SpriteComponent() = default;
    SpriteComponent(string id){
        setTex(id);
    }
    SpriteComponent(string id, bool isAnimated) // har man alla ska det animeras.
    {
        animated = isAnimated;
        Animation idle = Animation(0,2,150); //RadMedAnim,AntalBilder,TidMellanBildByten
        Animation walkVertical = Animation(0,2,100);
        Animation walkHorizontal = Animation(1,2,100); 
       
        Animation FlyingEagle = Animation(1,8,100); 

        animations.emplace("Idle", idle);
        animations.emplace("walkVertical", walkVertical);
        animations.emplace("walkHorizontal", walkHorizontal);

        animations.emplace("flyingEagle", FlyingEagle);

        Play("Idle");
       
        setTex(id);
        
    }
    ~SpriteComponent()
    {
    }
    void setTex(string id)
    {
        texture = Game::assets->GetTexture(id);
    }

    void init() override
    {
        
        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
      
    }

    void update() override
    {
       
        if(animated ){
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks()/ speed) % frames);
        }
    
        srcRect.y = animIndex * transform->height;

        destRect.x = static_cast<int>(transform->position.x)- Game::camera.x;
        destRect.y = static_cast<int>(transform->position.y)-Game::camera.y;
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;

    }

    void draw() override
    {
        
        TextureManager::Draw(texture, srcRect, destRect,spriteFlip);
    }

    void Play(const char* animName){//kör animationen.        
        frames = animations[animName].frames;
        animIndex = animations[animName].index;
        speed = animations[animName].speed;
    }
};

#endif