#include "GameObject.h"
#include "TextureManager.h"
GameObject::GameObject(const char *textureSheet, int x, int y)
{

    objTexture = TextureManager::LoadTexture(textureSheet);
    xpos = x;
    ypos = y;
}
void GameObject::Update()
{

    // här kommer det läggas till movement
    xpos++;
    ypos++;
    srcRect.h = 32; //spelarens start storlek
    srcRect.w = 32;
    srcRect.x = 0; // spelarens start position
    srcRect.y = 0;
    destRect.h = srcRect.h * 2; // spelarens nästa storlek
    destRect.w = srcRect.w * 2;
    destRect.x = xpos; // spelarens nästa position
    destRect.y = ypos;
}

void GameObject::Render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
GameObject::~GameObject()
{

}