#include "Player.h"
#include "Core.h"

#include <fstream>
string character[3] = {"Player00", "Player01", "Player02"};
string weapon[3] = {"PlayerBullet00", "PlayerBullet01", "PlayerBullet02"};

Player::Player(int _type):MainObject(0, 400, character[_type], 3, 8) {
        x = 185 + 270 / 2 - srcRect.w / 2;
        hp = 1;
        type = _type;
        shootTime = 0;
        allKill = isMagnet = isStar = isMurshroom = 0;
        starTime = murshroomTime = magnetTime = SDL_GetTicks();
}

Player::~Player() { }

void Player::Input() {
        if (Core::inGame && hp > 0 && !isStar && shootTime + 75 <= SDL_GetTicks()) {
            if (isMurshroom) {
                xBullet.push_back(new MainObject(x, y, weapon[type], 1, 2));
                xBullet.push_back(new MainObject(x + srcRect.w, y, weapon[type], 1, 2));
            } else xBullet.push_back(new MainObject(x + srcRect.w / 2, y, weapon[type], 1, 2));
            shootTime = SDL_GetTicks();
        }
        if (isStar && starTime + 2000 <= SDL_GetTicks()) {
            isStar = 0;
            allKill = 1;
            starTime = SDL_GetTicks();
        }
        if (isMurshroom && murshroomTime + 5000 <= SDL_GetTicks()) isMurshroom = 0;

        if (isMagnet && magnetTime + 3000 <= SDL_GetTicks()) isMagnet = 0;
}

void Player::Update() {
        MainObject::Update();

        if (hp == 0) {
            Mix_HaltMusic();
            Mix_HaltChannel(-1);
            Mix_PlayChannel(-1, Core::oSound->explosionSound, 0);

            hp--;
            isStar = isMagnet = isMurshroom = 0;
            Core::oExplosion->oList.push_back(new Effect(x, y, 0, "ExplosionPlayer", 1, 9));
            // ----- Get Informations
            int sco[10], id[10];
            ifstream rin("files/ranking.txt");
            for (int i = 0; i < 9; i++) rin >> sco[i] >> id[i];
            rin.close();
            id[9] = type;
            sco[9] = Core::score;
            // ----- Sort
            for (int i = 1; i < 10; i++)
                for (int j = 0; j < i; j++)
                    if (sco[i] >= sco[j]) {
                        swap(sco[i], sco[j]);
                        swap(id[i], id[j]);
                    }
            // ----- Rewrite the Highscore
            ofstream rout("files/ranking.txt");
            for (int i = 0; i < 9; i++) rout << sco[i] << ' ' << id[i] << endl;
            rout.close();
        }

        if (Core::inGame) {
            const Uint8 *keystate = SDL_GetKeyboardState(NULL);

            if (Core::inGame && keystate[SDL_SCANCODE_ESCAPE] && hp > 0) hp = 0;

            if (keystate[SDL_SCANCODE_LEFT]) {
                if (moveX >= -8) moveX = -8; else moveX -= 8;
                space = 8;
            }
            if (keystate[SDL_SCANCODE_RIGHT]) {
                if (moveX <= 8) moveX = 8; else moveX += 8;
                space = 16;
            }
            if (!(keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_RIGHT])) {
                space = 0;
                moveX = 0;
            }
            if (!(185 - srcRect.w / 2 <= x + moveX && x + moveX <= 455 - srcRect.w / 2)) x -= moveX;
        }
        // ----- Player's Bullets
        for (unsigned int i = 0; i < xBullet.size(); i++) {
            xBullet[i]->Update();
            if (xBullet[i]->y <= -xBullet[i]->srcRect.h) xBullet[i]->hp = 0;
            xBullet[i]->Destroy(xBullet, i);
        }
}

void Player::Draw(SDL_Renderer* rR) {
        if (hp > 0) MainObject::Draw(rR);
        for (unsigned int i = 0; i < xBullet.size(); i++) xBullet[i]->Draw(rR);
}

