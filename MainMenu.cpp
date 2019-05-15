#include "MainMenu.h"
#include "Core.h"

MainMenu::MainMenu():MainObject(320, 0, "MainMenu", 1, 2) {
        num = new MainObject(0, 0, "Number", 1, 11);
        for (int i = 0; i < 4; i++) {
            tittle[i] = new MainObject(50, 0, "Tittle", 1, 4);
            tittle[i]->FPS = 0;
            tittle[i]->frame = i;
        }
        tittle[0]->x = 185;
        cursor = new MainObject(249, 273, "Mouse", 1, 2);
        canPress = 1;
        posX = 0;
        posY = 1;
        posT = 0;
}

MainMenu::~MainMenu() { }

void MainMenu::Update(SDL_Event* event) {
        const Uint8 *keystate = SDL_GetKeyboardState(NULL);

        if (event->type == SDL_KEYUP) canPress = 1;
        if (event->type == SDL_KEYDOWN && canPress) {
            if (!keystate[SDL_SCANCODE_LEFT] && !keystate[SDL_SCANCODE_RIGHT]) {
            if (Core::rankin) {
                frame = 0;
                Core::oPlayer = new Player(posX);
                Mix_PlayChannel(-1, Core::oSound->decideSound, 0);
                if (Core::inGame) Core::oBackGround = new BackGround(-1);
                Core::inGame = 0;
                Core::rankin = 0;
            }
            else
            if (!keystate[SDL_SCANCODE_UP] && !keystate[SDL_SCANCODE_DOWN] && !keystate[SDL_SCANCODE_ESCAPE]) {
                Mix_PlayChannel(-1, Core::oSound->decideSound, 0);
                if (posY == 1) Core::inGame = Core::newGame = 1;
                if (posY == 2) Core::rankin = 1;
                if (posY == 3) Core::quitGame = 1;
            }
            }
        }

        if (canPress) {
            int moveCursor = 0;
            if (keystate[SDL_SCANCODE_UP]) moveCursor = -1;
            if (keystate[SDL_SCANCODE_DOWN]) moveCursor = 1;
            if (moveCursor != 0 && 0 <= posY + moveCursor && posY + moveCursor <= 3) {
                canPress = 0;
                posY += moveCursor;
                Mix_PlayChannel(-1, Core::oSound->mouseSound, 0);
            }

            moveCursor = 0;
            if (posY == 0) {
                posT = posX + 1;
                if (keystate[SDL_SCANCODE_LEFT]) moveCursor = -1;
                if (keystate[SDL_SCANCODE_RIGHT]) moveCursor = 1;
                if (moveCursor != 0 && 0 <= posX + moveCursor && posX + moveCursor <= 2) {
                    canPress = 0;
                    posX += moveCursor;
                    Core::oPlayer = new Player(posX);
                    Mix_PlayChannel(-1, Core::oSound->mouseSound, 0);
                }
            }
            if (posY == 1) posT = 0;
        }
        if (Core::rankin) frame = 1;
        MainObject::Update();

        if (tittle[posT]->x == -85) tittle[posT]->moveX = 45;
        if (tittle[posT]->x == 455) tittle[posT]->moveX = -45;
        for (int i = 0; i < 4; i++) {
            if (posT != i && tittle[i]->x == 185)
                if (tittle[posT]->x == -85)
                    tittle[i]->moveX = 45;
                    else tittle[i]->moveX = -45;
            }

        for (unsigned i = 0; i < 4; i++) {
            if (posT == i && tittle[i]->x == 185) tittle[i]->moveX = 0;
            if (posT != i && tittle[i]->x == -85) tittle[i]->moveX = 0;
            if (posT != i && tittle[i]->x == 455) tittle[i]->moveX = 0;
            tittle[i]->Update();
        }
}

void MainMenu::Draw(SDL_Renderer* rR) {
        if (Core::rankin) MainObject::Draw(rR);

        if (Core::inGame) return;
        MainObject::Draw(rR);

        if (Core::rankin) return;

        cursor->frame = 0;
        cursor->x = 249 - cursor->srcRect.w / 2;
		if (posY == 0) cursor->y = -100; else cursor->y = 275 + 37 * (posY - 1);
		cursor->Update();
        cursor->Draw(rR);

        cursor->frame = 1;
        cursor->x = 233 + 68 * posX;
        cursor->y = 213;
		cursor->Update();
        cursor->Draw(rR);

        for (unsigned i = 0; i < 4; i++) tittle[i]->Draw(rR);
}
