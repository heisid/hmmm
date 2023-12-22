#include <math.h>
#include "raylib.h"
#include "raymath.h"


typedef struct InitConfig {
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int ORIGIN_X;
    int ORIGIN_Y;
    char TITLE[20];
    int TARGET_FPS;
} InitConfig;

void doInitialization(InitConfig config);
void doDrawing(InitConfig config);
void doUpdate();

int main(void)
{
    InitConfig config = {
            1500,
            900,
            1500 / 2,
            900 / 2,
            "Cool shit",
            60
    };
    doInitialization(config);

    while (!WindowShouldClose())
    {
        doUpdate();
        doDrawing(config);
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

void doDrawing(InitConfig config) {
    BeginDrawing();

    ClearBackground(BLACK);
    DrawLine(0, config.ORIGIN_Y, config.SCREEN_WIDTH, config.ORIGIN_Y, RED);
    DrawLine(config.ORIGIN_X, 0, config.ORIGIN_X, config.SCREEN_HEIGHT, RED);

    int end = config.SCREEN_WIDTH / 2;
    int start = -1 * end;
    for (int x = start; x < end; x++) {
        float y = 100 * sinf((float)x/10);
        y *= -1;
        DrawPixelV(Vector2Add((Vector2){(float)x, y}, (Vector2){(float)config.ORIGIN_X, (float)config.ORIGIN_Y}), GREEN);
    }

    EndDrawing();
}