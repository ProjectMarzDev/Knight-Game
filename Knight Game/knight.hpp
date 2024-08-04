#include "raylib.h"
#include <fstream>

class Knight
{
    public:
    Knight();
    void draw();
    void tick(float deltaTime);
    void movement(float deltaTime);
    bool collision(Rectangle player, Rectangle tile);
    void loadLevel();
    private:
    Rectangle rect;
    //8x8
    Texture2D knight = LoadTexture("sprites/knight.png");
    Vector2 frame_count = {8.f,8.f};
    float image_scale = {2};
    float running_time{};
    float update_time{1.f/10.f};
    Vector2 running_frame_idle = {0,0};
    Vector2 running_frame_run = {0,2};
    float running = 3;
    bool isRunning = false;
    float direction = 1;
    //physics
    float velocity{};
    float gravity{1};

    //bounding box
    Rectangle bounds = {};      

    //movement
    float speed = 5;
    float jump = 8;

    //player jump boolean
    bool canJump = false;

    //toggle bounds
    bool showBounds = false;


    //blocks
    int map[15][15];
    Rectangle mapRect[15][15];
    float cellSize = 33.3f;

    //sounds
    Sound jump_sound = LoadSound("sounds/jump.wav");


    float jumpTimeTimer{};
    float jumpTime{.2f};

    bool canBigJump = false;
};