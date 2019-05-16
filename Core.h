#ifndef CORE_H
#define CORE_H

#include <map>
#include <SDL.h>
#include <cstdlib>
#include <iostream>
#include <SDL_image.h>

#include "Coin.h"
#include "Image.h"
#include "Sound.h"
#include "Bosses.h"
#include "Layout.h"
#include "Player.h"
#include "Enemies.h"
#include "MainMenu.h"
#include "Explosion.h"
#include "BackGround.h"

using namespace std;

class Core
{
    public:
        Core();
        virtual ~Core();

        void Input();
        void Update();
        void Draw();

        void mainLoop();

        static bool inGame, newGame, rankin, quitGame, fightBoss;
        static unsigned score, enemyWave;
        static Coin* oCoin;
        static Sound* oSound;
        static Enemies* oEnemies;
        static Player* oPlayer;
        static Explosion* oExplosion;
        static BackGround* oBackGround;
        static Image* oImage;
    private:
        SDL_Renderer* rR;
        SDL_Window* window;
        SDL_Event* mainEvent;

        Bosses* oBosses;
        Layout* oLayout;
        MainMenu* oMenu;

        Uint32 FPS = 60;
        Uint32 frameStart;
        Uint32 frameTime;
};

#endif
