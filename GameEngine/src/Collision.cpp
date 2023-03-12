#include "Collision.h"
#include "ECS/ColliderComponent.h"
bool Collision::AABB(const SDL_Rect &recA, const SDL_Rect &recB)
{

    if (recA.x + recA.w >= recB.x && // kolla om objektens rektanglar nuddar varran
        recB.x + recB.w >= recA.x &&
        recA.y + recA.h >= recB.y &&
        recB.y + recB.h >= recA.y)
    {
         cout << "träffade "<<endl;
        return true; // = collision
    }
    return false; // ingen collision
}

bool Collision::AABB(const ColliderComponent &colA, const ColliderComponent &colB)
{
    if(AABB(colA.collider,colB.collider)){
        cout << colA.tag << "träffade " << colB.tag<<endl;
        return true;      
    }
    else{
        return false;
    }

}