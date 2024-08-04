#include <iostream>
#include "raylib.h"
#include "knight.hpp"
#include "World.hpp"

int main()
{
    const int window_dimensions[2] = {500,500};

    InitWindow(window_dimensions[0], window_dimensions[1], "Subscribe To ProjectMarsDev!!");
    InitAudioDevice();

    SetTargetFPS(60);

    Knight player;

    //68 85 90
    Color background_color = {187, 222, 251, 100};

    World world;

    Music song = LoadMusicStream("music/time_for_adventure.mp3");

    PlayMusicStream(song);

    while(!WindowShouldClose())
    {
        BeginDrawing();
        UpdateMusicStream(song);
        ClearBackground(background_color);
        player.tick(GetFrameTime());
        world.draw();
        EndDrawing();
    }
    UnloadMusicStream(song);
    CloseWindow();
    return 0;
}