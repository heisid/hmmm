//
// Created by sid on 1/2/24.
//

#ifndef HMMM_CONFIG_H
#define HMMM_CONFIG_H

typedef struct Config {
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int ORIGIN_X;
    int ORIGIN_Y;
    char TITLE[20];
    int TARGET_FPS;
} Config;
extern Config config;

#endif //HMMM_CONFIG_H
