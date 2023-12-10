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
    float gravityConstant;
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
            .gravityConstant = 1.0f,
    };

    Ball luna = {
            .pos = {(float)config.SCREEN_WIDTH / 2, 0.0f + 60},
            .radius = 5,
            .mass = 25,
            .velocity = { 10.0f, 0.0f },
            .force = {0.0f, 0.0f},
            WHITE
    };

    Ball potato = {
            .pos = {(float)config.SCREEN_WIDTH / 2, (float)config.SCREEN_HEIGHT - 60},
            .radius = 5,
            .mass = 25,
            .velocity = { -10.0f, 0.0f },
            .force = {0.0f, 0.0f},
            YELLOW
    };

    Ball earth = {
            .pos = {(float)config.SCREEN_WIDTH / 2, (float)config.SCREEN_HEIGHT / 2 },
            .radius = 20,
            .mass = 700,
            .velocity = { 0.0f, 0.0f },
            .force = {0.0f, 0.0f},
            BLUE
    };

    Ball *balls[] = {&earth, &luna, &potato};

    while (!WindowShouldClose())
    {
        doUpdate(balls, 3, physics);
        doDrawing(balls, 3);
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

Vector2 computeGravity(Ball *ball1, Ball *ball2, Physics physics) {
    // Gravity felt by ball2
    Vector2 displacement = Vector2Subtract(ball1->pos, ball2->pos);
    float gravityMag = (physics.gravityConstant * ball1->mass * ball2->mass) / Vector2LengthSqr(displacement);
    return Vector2Scale(Vector2Normalize(displacement), gravityMag);
}

void doUpdate(Ball **balls, int totalBalls, Physics physics) {
    float dt = GetFrameTime();
    for (int i = 0; i < totalBalls; i++) {
        Ball *ball = balls[i];
        Vector2 gravityTotal = {0.0f, 0.0f};
        for (int j = 0; j < totalBalls; j++) {
            if (i != j) {
                Ball *otherBall = balls[j];
                Vector2 gravity = computeGravity(otherBall, ball, physics);
                gravityTotal = Vector2Add(gravityTotal, gravity);
            }
        }
        // Update position from last velocity
        ball->pos = Vector2Add(ball->pos, Vector2Scale(ball->velocity, dt));
        // Update velocity for next frame
        ball->velocity = Vector2Add(ball->velocity, Vector2Scale(gravityTotal, dt));
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