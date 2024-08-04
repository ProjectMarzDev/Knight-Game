#include "World.hpp"

World::World()
{
    loadLevel(); 
}
//16
void World::draw()
{
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            if(map[i][j] == 1)
            {
                DrawTextureEx(grass, {mapRect[i][j].x, mapRect[i][j].y}, 0.f, scale, WHITE);
            }

            if(map[i][j] == 2)
            {
                DrawTextureEx(dirt, {mapRect[i][j].x, mapRect[i][j].y}, 0.f, scale, WHITE);
            }
        }
    }
}

void World::loadLevel()
{
    std::ifstream worldData("levels/level1.data");
    
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            worldData >> map[i][j];

            if(map[i][j] == 0)
            {
                mapRect[i][j] = Rectangle{0,0,0,0};
            }
            else if(map[i][j] == 1 || map[i][j] == 2)
            {
                mapRect[i][j] = Rectangle{(float)j * cellSize, (float)i * cellSize,cellSize,cellSize};
            }
        }
    }
    worldData.close();
}