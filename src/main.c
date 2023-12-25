#include "raylib.h"
#include "raymath.h"


typedef struct Config {
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int ORIGIN_X;
    int ORIGIN_Y;
    char TITLE[20];
    int TARGET_FPS;
} Config;
Config config = {
        1500,
        900,
        1500 / 2,
        900 / 2,
        "Cool shit",
        60
};

void doInitialization();
Vector2 toCenter(Vector2 vector);
Vector2 toTopLeft(Vector2 vector);
Vector2 angle2HeadingVector(float angle);

void doDrawing();
void doUpdate();

int main(void)
{
    doInitialization();

    while (!WindowShouldClose())
    {
        doUpdate();
        doDrawing();
    }

    CloseWindow();

    return 0;
}

void doInitialization() {
    InitWindow(config.SCREEN_WIDTH, config.SCREEN_HEIGHT, config.TITLE);
    SetTargetFPS(config.TARGET_FPS);
}

Vector2 toCenter(Vector2 vector) {
    return (Vector2) {
        vector.x + (float)config.ORIGIN_X,
        -1 * (vector.y + (float)config.ORIGIN_Y)
    };
}

Vector2 toTopLeft(Vector2 vector) {
    return (Vector2) {
        vector.x - (float)config.ORIGIN_X,
        -1 * (vector.y - (float)config.ORIGIN_Y)
    };
}

Vector2 angle2HeadingVector(float angle) {
    // angle in degree
    angle = angle * (float)M_PI / 180;
    return (Vector2) {
        cosf(angle),
        sinf(angle)
    };
}

void doUpdate() {
    float dt = GetFrameTime();
}

void doDrawing() {
    BeginDrawing();

    ClearBackground(BLACK);

    EndDrawing();
}