#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
    TransformComponent *transform;
    SpriteComponent *sprite;

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override
    {
        if (Game::event.type == SDL_KEYDOWN)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w: //UPPÅT
                transform->velocity.y = -1;
                sprite->Play("walkVertical");
                sprite->spriteFlip = SDL_FLIP_NONE;
                break;
            case SDLK_s: //NEDÅT
                transform->velocity.y = 1;
                sprite->Play("walkVertical");
                sprite->spriteFlip = SDL_FLIP_VERTICAL;
                break;
            case SDLK_a: //VÄNSTER
                transform->velocity.x = -1;
                sprite->Play("walkHorizontal");
                sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                break;
            case SDLK_d: //HÖGER
                transform->velocity.x = 1;
                sprite->Play("walkHorizontal");
                 sprite->spriteFlip = SDL_FLIP_NONE;
                break;
            case SDLK_SPACE:
                cout << "bajsa";
                //bygg en skjut grej som gör att man bajsar.
                break;
            
            default:
            break;
            }
        }
        if (Game::event.type == SDL_KEYUP)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                transform->velocity.y = 0;
                sprite->Play("Idle");
                break;
            case SDLK_s:
                transform->velocity.y = 0;
                sprite->Play("Idle");
                break;
            case SDLK_a:
                transform->velocity.x = 0;
                sprite->Play("Idle");
                break;
            case SDLK_d:
                transform->velocity.x = 0;
                sprite->Play("Idle");
              
                
                break;
            case SDLK_SPACE:
                break;
            case SDLK_ESCAPE:
                Game::isRunning = false;
                break;

            default:
            break;
            }
        }
    }
};

#endif