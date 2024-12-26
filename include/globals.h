#pragma once

#include "lasermanager.h"
#include "soundmanager.h"
#include "player.h"
#include <iostream>

#define LOG(x) std::cout << x << std::endl

enum State
{
    SPLASH_SCREEN,
    MENU,
    GAME
};

class Globals
{
public:
    static int canvasWidth;
    static int canvasHeight;
    static int gameWidth;
    static int gameHeight;
    static LaserManager *laserManager;
    static SoundManager *soundManager;
    static Player *player;
    static State state;
};