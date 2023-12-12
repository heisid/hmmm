#include "raylib.h"
#include "raymath.h"


typedef struct InitConfig {
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    char TITLE[20];
    int TARGET_FPS;
} InitConfig;

void doInitialization(InitConfig config);
void doDrawing();
void doUpdate();

int main(void)
{
    InitConfig config = {
            1500,
            900,
            "Just a fucking test",
            60
    };
    doInitialization(config);

    while (!WindowShouldClose())
    {
        doUpdate();
        doDrawing();
    }

    CloseWindow();

    return 0;
}

void doInitialization(InitConfig config) {
    InitWindow(config.SCREEN_WIDTH, config.SCREEN_HEIGHT, config.TITLE);
    SetTargetFPS(config.TARGET_FPS);
}

void doUpdate() {
    float dt = GetFrameTime();
}

void doDrawing() {
    BeginDrawing();

    ClearBackground(BLACK);

    EndDrawing();
}