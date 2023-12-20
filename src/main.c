#include <stdlib.h>
#include <stdio.h>

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

typedef struct Line {
    Vector2 start;
    Vector2 end;
    Color color;
} Line;

typedef struct Object {
    int posX;
    int posY;
    float radius;
    Color color;
    float charge;
} Object;

typedef struct VectorField {
    int colSize;
    int rowSize;
    int spacing;
    Line **lines;
} VectorField;

void Initialize(Config config);
void InitializeVectorField(VectorField *vectorField, int colSize, int rowSize);
void doDrawing(VectorField *vectorField, int colSize, int rowSize, Object *object);
void doUpdate(VectorField *vectorField, Object *object);

int main(void)
{
    Config config = {
            1500,
            900,
            1500 / 2,
            900 / 2,
            "Cool Thing",
            60
    };
    Initialize(config);

    int spacing = 20;
    int colSize = config.SCREEN_WIDTH / spacing - 1;
    int rowSize = config.SCREEN_HEIGHT / spacing - 1;
    Line **lines = NULL;
    VectorField vectorField = {
            .colSize = colSize,
            .rowSize = rowSize,
            .spacing = spacing,
            .lines = lines
    };
    InitializeVectorField(&vectorField, colSize, rowSize);

    Object positiveCharge = {
            .posX = config.ORIGIN_X,
            .posY = config.ORIGIN_Y,
            .radius = 20,
            .color = RED,
            .charge = 10
    };

    while (!WindowShouldClose())
    {
        doUpdate(&vectorField, &positiveCharge);
        doDrawing(&vectorField, colSize, rowSize, &positiveCharge);
    }

    CloseWindow();

    return 0;
}

void Initialize(Config config) {
    InitWindow(config.SCREEN_WIDTH, config.SCREEN_HEIGHT, config.TITLE);
    SetTargetFPS(config.TARGET_FPS);
}

void MemAllocFailed(char *source) {
    printf("Memory allocation for %s failed", source);
    exit(42);
}

float getRndAngle() {
    float nMax = 360;
    return (float)rand() / ((float)RAND_MAX / nMax); // NOLINT(cert-msc30-c, cert-msc50-cpp)
}

void InitializeVectorField(VectorField *vectorField, int colSize, int rowSize) {
    vectorField->lines = malloc(rowSize * sizeof(Line*));
    for (int i = 0; i < rowSize; i++) {
        vectorField->lines[i] = malloc(colSize * sizeof(Line));
        for (int j = 0; j < colSize; j++) {
            Vector2 start = {
                    (float)((j + 1) * vectorField->spacing),
                    (float)((i + 1) * vectorField->spacing)
            };
            Vector2 end = {start.x + 5, start.y - 5};
            Line line = {
                    .start = start,
                    .end = end,
                    .color = WHITE
            };
            vectorField->lines[i][j] = line;
        }
    }
}

void doUpdate(VectorField *vectorField, Object *object) {
    float dt = GetFrameTime();
}

void doDrawing(VectorField *vectorField, int colSize, int rowSize, Object *object) {
    BeginDrawing();

    ClearBackground(BLACK);

    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            DrawLineV(vectorField->lines[i][j].start, vectorField->lines[i][j].end, vectorField->lines[i][j].color);
        }
    }
    DrawCircle(object->posX, object->posY, object->radius, object->color);

    EndDrawing();
}