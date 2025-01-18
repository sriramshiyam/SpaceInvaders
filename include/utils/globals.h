#pragma once

#include <iostream>
#include <raylib.h>
#include "manager/lasermanager.h"
#include "manager/soundmanager.h"
#include "manager/enemymanager.h"
#include "manager/combomanager.h"
#include "manager/explosionmanager.h"
#include "sprite/player.h"

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
    static EnemyManager *enemyManager;
    static ComboManager *comboManager;
    static ExplosionManager *explosionManager;
    static Player *player;
    static State state;
    static void *hud;
    static Font font;
};