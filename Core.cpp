#include "Core.h"

bool Core::inGame;
bool Core::rankin;
bool Core::newGame;
bool Core::quitGame;
bool Core::fightBoss;

unsigned Core::score;
unsigned Core::enemyWave;

Coin* Core::oCoin;
Image* Core::oImage;
Sound* Core::oSound;
Player* Core::oPlayer;
Enemies* Core::oEnemies;
Explosion* Core::oExplosion;
BackGround* Core::oBackGround;

Core::Core() {
        SDL_Init(SDL_INIT_EVERYTHING);
        window = SDL_CreateWindow("The TwikleStar Sprites", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_FULLSCREEN);
        if (window == NULL) quitGame = 1; else quitGame = 0;
        rR = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        mainEvent = new SDL_Event();

        oSound = new Sound();
        oImage = new Image(rR);
        oLayout = new Layout();
        oMenu = new MainMenu();
        oPlayer = new Player(0);
        oBackGround = new BackGround(-1);
        quitGame = inGame = newGame = rankin = 0;
}

Core::~Core() {
        delete oCoin;
        delete oImage;
        delete oSound;
        delete oLayout;
        delete oBosses;
        delete oPlayer;
        delete oEnemies;
        delete oExplosion;
        delete oBackGround;

        SDL_Quit();
        IMG_Quit();
}

void Core::mainLoop() {
        srand(SDL_GetTicks());
        while (mainEvent->type != SDL_QUIT) {
            frameStart = SDL_GetTicks();
            SDL_PollEvent(mainEvent);
            if (quitGame) break;

            SDL_RenderClear(rR);
            Input();
            Update();
            Draw();
            SDL_RenderPresent(rR);

            frameTime = SDL_GetTicks() - frameStart;
            if (unsigned(frameTime) < unsigned(1000 / FPS)) SDL_Delay(unsigned(1000 / FPS) - frameTime);
        }
}

void Core::Input() {
        oPlayer->Input();
        if (inGame) {
            oCoin->Bonus();
            oBosses->Spawn();
            oEnemies->Spawn();
        }
}

void Core::Update() {
        oBackGround->Update();
        oPlayer->Update();
        if (inGame) {
            oExplosion->Update();
            oEnemies->Update();
            oBosses->Update();
            oCoin->Update();
        }
        if (!inGame || rankin) oMenu->Update(mainEvent);
        if (newGame) {
            newGame = fightBoss = 0;
            enemyWave = score = 0;
            oCoin = new Coin();
            oBosses = new Bosses();
            oEnemies = new Enemies();
            oExplosion = new Explosion();
            Mix_PlayMusic(oSound->bgm, -1);
        }
}

void Core::Draw() {
        oBackGround->Draw(rR);
        if (inGame) {
            oExplosion->Draw(rR);
            oCoin->Draw(rR);
            oEnemies->Draw(rR);
            if (fightBoss) oBosses->Draw(rR);
        } else oMenu->Draw(rR);
        oPlayer->Draw(rR);
        oMenu->Draw(rR);
        oLayout->Draw(rR);
}
