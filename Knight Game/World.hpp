#include "raylib.h"
#include <fstream>
#include <iostream>

class World
{
    public:
    World();
    void draw();
    void loadLevel();

    private:
    int map[15][15];
    Rectangle mapRect[15][15];
    Texture2D grass = LoadTexture("sprites/grass.png");
    Texture2D dirt = LoadTexture("sprites/dirt.png");
    float cellSize = 33.3f;
    float scale = 2.08125f;

};