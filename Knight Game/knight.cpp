#include "knight.hpp"
#include <iostream>

Knight::Knight()
{
    rect = Rectangle{0,0,static_cast<float>(knight.width / frame_count.x) * image_scale,static_cast<float>(knight.height / frame_count.y) * image_scale};
    //10+4
    bounds.width = rect.width;
    bounds.height = rect.height;
    //scale the collider to the character
    bounds.height = 16 * image_scale;
    bounds.width = 10 * image_scale;
    loadLevel();
}

void Knight::draw()
{
    DrawTexture(knight, static_cast<int>(rect.x), static_cast<int>(rect.y), WHITE);
}

void Knight::tick(float deltaTime)
{
    running_time += deltaTime;

    if(running_time >= update_time)
    {
        running_time = 0;
        if(isRunning)
        {
            running_frame_idle.x = 0;
            running_frame_run.x++;
            if(running_frame_run.x > 8)
            {
                running_frame_run.x = 0;
            }
        }
        else if(!isRunning)
        {
            running_frame_run.x = 0;
            running_frame_idle.x++;
            if(running_frame_idle.x > 3)
            {
                running_frame_idle.x = 0;
            }
        }
    }
    movement(deltaTime);
    //running_frame_idle * static_cast<float>(knight.width) * image_scale
    Rectangle source = {(isRunning ? running_frame_run.x : running_frame_idle.x) * static_cast<float>(knight.width) / frame_count.x ,static_cast<float>(knight.height / frame_count.y) * (isRunning ? running_frame_run.y : running_frame_idle.y), static_cast<float>(knight.width/frame_count.x), static_cast<float>(knight.height / frame_count.y)};
    Rectangle dest = {rect.x,rect.y, static_cast<float>(knight.width / frame_count.x) * image_scale,static_cast<float>(knight.height/frame_count.y) * image_scale};
    source.width *= direction;
    DrawTexturePro(knight, source, dest, {0.f,0.f}, 0.f, WHITE);
    if(showBounds)
    {
        DrawRectangleLinesEx(bounds, 5.f, RED);
    }
}

void Knight::movement(float deltaTime)
{
    float dx{};
    float dy{};

    //player movement
    int horizontal = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
    dx = horizontal * speed;
    direction = (dx > 0) ? 1 : (dx < 0) ? -1 : direction;
    isRunning = (horizontal > 0) ? true : (horizontal < 0) ? true : false;

    //gravity

    if(IsKeyPressed(KEY_SPACE) && canJump)
    {
        canJump = false;
        velocity = -jump;
        PlaySound(jump_sound);

        canBigJump = true;
        jumpTimeTimer = jumpTime;
    }

    if(IsKeyDown(KEY_SPACE) && canBigJump)
    {
        if(jumpTimeTimer > 0)
        {
            velocity = -jump;
            jumpTimeTimer -= deltaTime;
        }
        else
        {
            canBigJump = false;
        }
    }


    // if(IsKeyPressed(KEY_LEFT_SHIFT))
    // {
    //     showBounds = !showBounds;
    // }

    if(IsKeyPressed(KEY_UP))
    {
        image_scale += .1;
        bounds.height = 16 * image_scale;
        bounds.width = 10 * image_scale;
    }
    else if(IsKeyPressed(KEY_DOWN))
    {
        image_scale -= .1;
        bounds.height = 16 * image_scale;
        bounds.width = 10 * image_scale;
    }

    velocity += gravity;
    if(velocity > 10)
    {
        velocity = 10;
    }
    dy += velocity;

    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            if(collision(Rectangle{bounds.x, bounds.y + dy, bounds.width, bounds.height}, mapRect[i][j]))
            {
                if(velocity < 0)
                {
                    dy = (mapRect[i][j].y + mapRect[i][j].height) - bounds.y;
                    velocity = 0;
                }
                else if(velocity > 0)
                {
                    canJump = true;
                    velocity = 0;
                    dy = mapRect[i][j].y - (bounds.y + bounds.height);
                }
            }

            if(collision(Rectangle{bounds.x + dx, bounds.y, bounds.width, bounds.height}, mapRect[i][j]))
            {
                dx = 0;
            }
        }
    }

    

    //add movement
    rect.x += dx;
    rect.y += dy;
    //correct / update the bounds
    bounds.x = + 11 * image_scale + rect.x;
    bounds.y = rect.y + 12 * image_scale;

    //floor collision
    if(bounds.y + bounds.height >= 500)
    {
        bounds.y = 500 - bounds.height;
        velocity = 0;
        rect.y = 500 - rect.height + 4 * image_scale;
    }

    // std::cout << rect.y << " " << static_cast<float>(rect.height / frame_count.y) << '\n';
}

bool Knight::collision(Rectangle player, Rectangle tile)
{
    return player.x + player.width > tile.x &&
    player.x < tile.x + tile.width &&
    player.y + player.height > tile.y &&
    tile.y + tile.height > player.y;
}

void Knight::loadLevel()
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