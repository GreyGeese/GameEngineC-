#ifndef MAP_H
#define MAP_H

#include <string>
using namespace std;

class Map
{
public:
    Map(string tID, int ms, int ts);
    ~Map();
    // tar in en map av siffror som sedan renderars ut med tileComponent.h
     
     void AddTile(int srcX, int srcY, int xpos, int ypos);
     void LoadMap(string path,int sizeX, int sizeY);

private:
   string texID;
   int mapScale;
   int tileSize;
   int scaledSize;
};
#endif