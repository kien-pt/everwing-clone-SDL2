#include "Enemies.h"
#include "Core.h"

Enemies::Enemies() {
        moveY = 3;
        mainHP = 5;
        attaccTime = 10000;
        theLastEnemyPosition = 0;
        bonusTime = SDL_GetTicks();
        attackTime = SDL_GetTicks();
        waitTime = rand() % 2500 + 500;
        healthBar = new MainObject(0, 0, "HealthBar", 3, 1);
}

Enemies::~Enemies() { }

void Enemies::Spawn() {
        // ----- Main Enemies
        theLastEnemyPosition += moveY;
        if (Core::oPlayer->isStar) {
            list02.resize(0);
            theLastEnemyPosition += 6 * moveY;
        }
        if ((!Core::fightBoss && theLastEnemyPosition >= 200)) {
            theLastEnemyPosition = -68;
            for (unsigned i = 0; i < 5; i++)
            list01.push_back(new MainObject(212 + i * 54, -68, "EnemyMain", 5, 6));
            if (!Core::oPlayer->isStar) Core::enemyWave++;
        }
        // ----- Pause
        if (Core::fightBoss) theLastEnemyPosition = -1000;
        // ----- Play
        if (!Core::fightBoss && theLastEnemyPosition <= -100) {
            theLastEnemyPosition = 0;
            attackTime = SDL_GetTicks();
        }

        if (!(Core::oPlayer->isStar || Core::fightBoss) && attackTime + waitTime <= SDL_GetTicks()) {
            list02.push_back(new MainObject(185 + rand() % 270, -80, "EnemyAttack", 3, 4));
            waitTime = rand() % attaccTime;
            attackTime = SDL_GetTicks();
        }

        if (!Core::fightBoss && bonusTime + 120000 <= SDL_GetTicks()) {
            list03.push_back(new MainObject(185 + 270 / 2, -60, "EnemyBonus", 3, 5));
            bonusTime = SDL_GetTicks();
            if (!Core::fightBoss) bonusTime -= 1000000;
        }
}

void Enemies::SpawnCoin(vector <MainObject*> & oVector, int k, int p) {
        float _x = oVector[k]->x + rand() % 58 - 32;
        float _y = oVector[k]->y - 32;
        Core::oCoin->oList.push_back(new MainObject(_x, _y, "Coin", 8, 8));
        Core::oCoin->oList[Core::oCoin->oList.size() - 1]->space = p * 8;
        Core::oCoin->oList[Core::oCoin->oList.size() - 1]->moveX = (rand() % 2000 - 1000) / 1000;
        Core::oCoin->oList[Core::oCoin->oList.size() - 1]->moveY = - (rand() % 10000 - 5000) / 1000;
}

void Enemies::Update() {
        if (Core::oPlayer->allKill) {
            Core::oPlayer->allKill = 0;
            for (unsigned int i = 0; i < list01.size(); i++) list01[i]->hp = 0;
        }

        for (unsigned int i = 0; i < list01.size(); i++) {
            CollisionWithBullet(list01, i);

            if (list01[i]->hp <= 0) {
                int _space = list01[i]->space;
                float _x = list01[i]->x + 68 / 2;
                float _y = list01[i]->y + 54 / 2;
                Mix_PlayChannel(-1, Core::oSound->coinSound[rand() % 5], 0);
                Core::oExplosion->oList.push_back(new Effect(_x, _y, _space, "ExplosionBefore", 5, 6));

                if (rand() % 25 == 0)
                Core::oCoin->Spawn(list01[i]->x, list01[i]->y, 68, 5, -1);
                else Core::oCoin->Spawn(list01[i]->x, list01[i]->y, 68, 1, 1);
            }

            list01[i]->Destroy(list01, i); if (i >= list01.size()) break;

            if (Core::oPlayer->isStar) {
                list01[i]->y += 6 * moveY;
                if (list01[i]->y >= 350 && list01[i]->hp != 999) {
                    if (rand() % 25 == 0)
                    Core::oCoin->Spawn(list01[i]->x, list01[i]->y, 68, 5, -1);
                    else Core::oCoin->Spawn(list01[i]->x, list01[i]->y, 68, 1, 1);

                    Mix_HaltChannel(-1);
                    list01[i]->hp = list01[i]->maxHP = 999;
                    Mix_PlayChannel(-1, Core::oSound->coinSound[rand() % 5], 0);
                }
            }
            list01[i]->Update();
        }

        for (unsigned int i = 0; i < list02.size(); i++) {
            list02[i]->Update();
            if (list02[i]->y > 480) list02[i]->hp = 0;
            list02[i]->Destroy(list02, i);
        }

        for (unsigned int i = 0; i < list03.size(); i++) {
            list03[i]->Update();
            if (list03[i]->y > 600) list03[i]->hp = 0;
            if (list03[i]->hp <= 0) {
                bonusTime = SDL_GetTicks();
                int _space = list03[i]->space;
                float _x = list03[i]->x + list03[i]->srcRect.w / 2;
                float _y = list03[i]->y + list03[i]->srcRect.h / 2;
                Core::oExplosion->oList.push_back(new Effect(_x, _y, (_space / 5) * 6, "ExplosionBonus", 3, 6));
            }

            list03[i]->Destroy(list03, i);
            CollisionWithBullet(list03, i);

            if (list03[i]->moveX < 0 && list03[i]->x <= 153) list03[i]->moveX = - list03[i]->moveX;
            if (list03[i]->moveX > 0 && list03[i]->x >= 423) list03[i]->moveX = - list03[i]->moveX;

            if (list03[i]->y >= 400 - list03[i]->srcRect.h || (Core::fightBoss && list01[list01.size() - 1]->y >= 480)) {
                list03[i]->moveX = 0;
                list03[i]->moveY = 3;
            }
        }
}

void Enemies::CollisionWithBullet(vector <MainObject*> & oVector, int k) {
        for (unsigned i = 0; i < Core::oPlayer->xBullet.size(); i++) {
            if (oVector[k]->CollisionWith(Core::oPlayer->xBullet[i])) {
                oVector[k]->hp--;
                Core::oPlayer->xBullet[i]->hp = 0;
                if (oVector[k]->tag == "EnemyBonus") {
                    if (rand() % 30 == 0)
                    Core::oCoin->Spawn(oVector[k]->x, oVector[k]->y, 68, 5, -1);
                    else Core::oCoin->Spawn(oVector[k]->x, oVector[k]->y, 68, 1, 1);
                    Mix_PlayChannel(-1, Core::oSound->coinSound[rand() % 5], 0);
                }
            }
        }
}

void Enemies::DrawHealthBar(SDL_Renderer* rR, vector <MainObject*> & oVector, int k) {
        healthBar->x = oVector[k]->x + 10;
        healthBar->y = oVector[k]->y + oVector[k]->srcRect.h + 3;
        healthBar->frame = 0;
        healthBar->Update();
        healthBar->Draw(rR);

        int temp = int(float(oVector[k]->hp) / float(oVector[k]->maxHP) * 21);
        for (int i = 0; i <= temp; i++) {
            healthBar->x = oVector[k]->x + 12 + 2 * i;
            healthBar->y = oVector[k]->y + oVector[k]->srcRect.h + 3;
            healthBar->frame = 2;
            healthBar->Update();
            healthBar->Draw(rR);
        }
}

void Enemies::Draw(SDL_Renderer* rR) {
        for (unsigned int i = 0; i < list01.size(); i++) {
            list01[i]->Draw(rR);
            DrawHealthBar(rR, list01, i);
        }
        for (unsigned int i = 0; i < list02.size(); i++) list02[i]->Draw(rR);
        for (unsigned int i = 0; i < list03.size(); i++) {
            list03[i]->Draw(rR);
            DrawHealthBar(rR, list03, i);
        }
}
