#include <stdlib.h>
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
        800,
        600,
        800 / 2,
        600 / 2,
        "Gw bikin apaan sih",
        60
};

void doInitialization();
Vector2 toCenter(Vector2 vector);
Vector2 toTopLeft(Vector2 vector);
Vector2 angle2HeadingVector(float angle);

typedef struct Object {
    Vector2 pos;
    float radius;
    Color color;
    float headingAngle;
    float distanceTraveled;
} Object;

void doDrawing(Object *object);
void doUpdate(Object *object);

int main(void)
{
    doInitialization();
    Object object = {
            .pos = (Vector2) {0, 0},
            .radius = 20.0f,
            .color = BLUE,
            .headingAngle = 90,
            .distanceTraveled = 0
    };

    while (!WindowShouldClose())
    {
        doUpdate(&object);
        doDrawing(&object);
    }

    CloseWindow();

    return 0;
}

void doInitialization() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(config.SCREEN_WIDTH, config.SCREEN_HEIGHT, config.TITLE);
    SetTargetFPS(config.TARGET_FPS);
}

Vector2 toCenter(Vector2 vector) {
    // Used only for drawing, any other calculation using raylib style coordinate (0, 0) top left. x = left-right, y = top-bottom
    return (Vector2) {
        vector.x + (float)config.ORIGIN_X,
        (-1 * vector.y) + (float)config.ORIGIN_Y
    };
}

Vector2 toTopLeft(Vector2 vector) {
    return (Vector2) {
        vector.x - (float)config.ORIGIN_X,
        (-1 * vector.y) - (float)config.ORIGIN_Y
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

void doUpdate(Object *object) {
    float dt = GetFrameTime();
    config.SCREEN_WIDTH = GetScreenWidth();
    config.SCREEN_HEIGHT = GetScreenHeight();
    config.ORIGIN_X = config.SCREEN_WIDTH / 2;
    config.ORIGIN_Y = config.SCREEN_HEIGHT / 2;
    float speed = 500.0f;
    if (object->distanceTraveled <= 100) {
        float nextPosDistance = speed * dt;
        object->distanceTraveled += nextPosDistance;
        Vector2 headingVector = angle2HeadingVector(object->headingAngle);
        Vector2 nextPos = Vector2Add(Vector2Scale(headingVector, nextPosDistance), object->pos);
        if (nextPos.x - object->radius < -1 * (float)config.SCREEN_WIDTH / 2) nextPos.x = -1 * ((float)config.SCREEN_WIDTH / 2) + object->radius;
        if (nextPos.x + object->radius > (float)config.SCREEN_WIDTH / 2) nextPos.x = ((float)config.SCREEN_WIDTH / 2) - object->radius;
        if (nextPos.y - object->radius < -1 * (float)config.SCREEN_HEIGHT / 2) nextPos.y = -1 * ((float)config.SCREEN_HEIGHT / 2) + object->radius;
        if (nextPos.y + object->radius > (float)config.SCREEN_HEIGHT / 2) nextPos.y = ((float)config.SCREEN_HEIGHT / 2) - object->radius;
        object->pos = nextPos;
    } else {
        object->headingAngle = fmodf(object->headingAngle + 15, 360.0f);
        object->headingAngle = (float)rand()/(float)(RAND_MAX/360);
        object->distanceTraveled = 0;
    }
}

void doDrawing(Object *object) {
    BeginDrawing();

    ClearBackground(BLACK);
    DrawCircleV(toCenter(object->pos), object->radius, object->color);
    DrawText(TextFormat("Heading: %f", object->headingAngle), 50, 50, 20, RED);

    EndDrawing();
}