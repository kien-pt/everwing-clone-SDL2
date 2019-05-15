#include "Coin.h"
#include "Core.h"
#include <cmath>

Coin::Coin() { }

Coin::~Coin() { }

void Coin::Bonus() {
        for (int i = 5; i < 8; i++) {
            if (Core::fightBoss && (i == 5 || i == 7)) break;
            if (rand() % 1000 == i) {
                oList.push_back(new MainObject(185 + rand() % 238, -64, "Coin", 8, 8));
                oList[oList.size() - 1]->space = 8 * i;
                oList[oList.size() - 1]->moveX = (rand() % 2000 - 1000) / 1000;
            }
        }
}

void Coin::Spawn(float x, float y, int w, int k, int d) {
        for (int i = 0; i < k; i++) {
            int dd = d;
            if (dd == -1) dd = rand() % 3;
            for (int j = 0; j < dd; j++) {
                oList.push_back(new MainObject(x + rand() % w, y - 32, "Coin", 8, 8));
                oList[oList.size() - 1]->space = i * 8;
                oList[oList.size() - 1]->moveX = (rand() % 2000 - 1000) / 1000;
                oList[oList.size() - 1]->moveY = - (rand() % 10000 - 5000) / 1000;
            }
        }
}

void Coin::Update() {
        for (unsigned i = 0; i < oList.size(); i++) {
            if ((Core::oPlayer->hp > 0 || oList[i]->space / 8 <= 4) && oList[i]->CollisionWith(Core::oPlayer)) {
                if (Core::oPlayer->hp > 0) {
                    oList[i]->hp = 0;
                    switch (oList[i]->space / 8) {
                        case 0: Core::score += 1;
                                break;
                        case 1: Core::score += 10;
                                break;
                        case 2: Core::score += 20;
                                break;
                        case 3: Core::score += 50;
                                break;
                        case 4: Core::score += 100;
                                break;
                        case 5: Core::oPlayer->isMagnet = 1;
                                Core::oPlayer->magnetTime = SDL_GetTicks();
                                break;
                        case 6: Core::oPlayer->isMurshroom = 1;
                                Core::oPlayer->murshroomTime = SDL_GetTicks();
                                break;
                        case 7: Core::oPlayer->isStar = 1;
                                Core::oPlayer->starTime = SDL_GetTicks();
                                break;
                        default: break;
                    }
                }
            }
            if (oList[i]->y > 480) oList[i]->hp = 0;
            oList[i]->Destroy(oList, i);
            oList[i]->Update();
            float distance = pow(Core::oPlayer->x - oList[i]->x, 2) + pow(Core::oPlayer->y - oList[i]->y, 2);
            if (Core::oPlayer->isMagnet && distance <= 150 * 150) {
                oList[i]->moveX = (Core::oPlayer->x - oList[i]->x) / 10;
                oList[i]->moveY = (Core::oPlayer->y - oList[i]->y) / 10;
            }
            if (!Core::oPlayer->isMagnet || distance > 150 * 150) oList[i]->moveY += 0.25;
        }
}

void Coin::Draw(SDL_Renderer* rR) {
        for (unsigned i = 0; i < oList.size(); i++) oList[i]->Draw(rR);
}

