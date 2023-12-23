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
    float prevX;
    float prevY0, prevY1, prevY2;
    for (int x = start; x < end; x++) {
        float y0 = 100 * sinf((float)x / 10);
        float y1 = 100 * cosf((float)x / 20);
        float y2 = y0 + y1;
        y0 *= -1;
        y1 *= -1;
        y2 *= -1;
        if (x != start) {
//            DrawLineV((Vector2){prevX, prevY0}, Vector2Add((Vector2){(float)x, y0}, (Vector2){(float)config.ORIGIN_X, (float)config.ORIGIN_Y}), GREEN);
//            DrawLineV((Vector2){prevX, prevY1}, Vector2Add((Vector2){(float)x, y1}, (Vector2){(float)config.ORIGIN_X, (float)config.ORIGIN_Y}), BLUE);
            DrawLineV((Vector2){prevX, prevY2}, Vector2Add((Vector2){(float)x, y2}, (Vector2){(float)config.ORIGIN_X, (float)config.ORIGIN_Y}), ORANGE);
        }
        prevX = (float)config.ORIGIN_X + (float)x;
        prevY0 = (float)config.ORIGIN_Y + y0;
        prevY1 = (float)config.ORIGIN_Y + y1;
        prevY2 = (float)config.ORIGIN_Y + y2;
    }

    EndDrawing();
}