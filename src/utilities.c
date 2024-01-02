//
// Created by sid on 1/2/24.
//
#include "raymath.h"
#include "utilities.h"
#include "config.h"

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