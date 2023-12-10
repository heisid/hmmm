#include "raylib.h"
#include "raymath.h"


typedef struct InitConfig {
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    char TITLE[20];
    int TARGET_FPS;
} InitConfig;

typedef struct Ball {
    Vector2 pos;
    float radius;
    float mass;
    Vector2 velocity;
    Vector2 force;
    Color color;
} Ball;

typedef struct Physics {
    Vector2 gravityVector;
    float dampeningFactor;
} Physics;

void doInitialization(InitConfig config);
void doDrawing(Ball **balls, int totalBalls);
void doUpdate(Ball **balls, int totalBalls, Physics physics);

int main(void)
{
    InitConfig config = {
            800,
            500,
            "Just a fucking test",
            60
    };
    doInitialization(config);

    Physics physics = {
            .gravityVector = (Vector2){0.0f, 6.0f},
            .dampeningFactor = 0.8f
    };

    Ball greenBall = {
            .pos = {(float)config.SCREEN_WIDTH / 2, 0.0f + 20},
            .radius = 20,
            .mass = 1,
            .velocity = { 0.0f, 0.0f },
            .force = physics.gravityVector,
            GREEN
    };

    Ball *balls[] = {&greenBall};

    while (!WindowShouldClose())
    {
        doUpdate(balls, 1, physics);
        doDrawing(balls, 1);
    }

    CloseWindow();

    return 0;
}

void doInitialization(InitConfig config) {
    InitWindow(config.SCREEN_WIDTH, config.SCREEN_HEIGHT, config.TITLE);
    SetTargetFPS(config.TARGET_FPS);
}

//float pix2m(int pixels) {
//    // Pixel to meter conversion, 1 pixel = 1 cm
//    return 0.01f * (float)pixels;
//}
//
//int m2pix(float metres) {
//    return (int)floorf(metres / 0.01f);
//}

void doUpdate(Ball **balls, int totalBalls, Physics physics) {
    float dt = GetFrameTime();
    for (int i = 0; i < totalBalls; i++) {
        Ball *ball = balls[i];
        // Update position from last velocity
        ball->pos = Vector2Add(ball->pos, Vector2Scale(ball->velocity, dt));
        // Update velocity for next frame
        ball->velocity = Vector2Add(ball->velocity, Vector2Scale(physics.gravityVector, dt));
    }
}

void doDrawing(Ball **balls, int totalBalls) {
    BeginDrawing();

    ClearBackground(BLACK);

    for (int i = 0; i < totalBalls; i++) {
        Ball *ball = balls[i];
        DrawCircleV(ball->pos, ball->radius, ball->color);
    }

    EndDrawing();
}