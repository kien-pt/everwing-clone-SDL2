#include "Bosses.h"
#include "Core.h"

string boss[3] = {"Boss00", "Boss01", "Boss02"};
int sheetColumn[3] = {6, 4, 5};

Bosses::Bosses() {
        stt = 0;
        bossHP = 100;
        order[0] = rand() % 3;
        while (1) {
            order[1] = rand() % 3;
            if (order[1] != order[0]) break;
        }
        while (1) {
            order[2] = rand() % 3;
            if (order[2] != order[0] && order[2] != order[1]) break;
        }
}

Bosses::~Bosses() { }

void Bosses::Spawn() {
        if (Core::oPlayer->hp >0 && !Core::fightBoss && Core::enemyWave >= 30) {
            bossHP += 50;
            Core::fightBoss = 1;
            xBoss = new Boss(order[stt++ % 3], bossHP);
            Core::oEnemies->mainHP = min(10, Core::oEnemies->mainHP + 1);
            Core::oEnemies->attaccTime = max(5000, Core::oEnemies->attaccTime - 1000);
        }
}

void Bosses::Update() {
        if (!Core::fightBoss) return;
        xBoss->Update();

        for (unsigned i = 0; i < Core::oPlayer->xBullet.size(); i++) {
            if (xBoss->CollisionWith(Core::oPlayer->xBullet[i])) {
                if (xBoss->isReady) xBoss->hp--;
                Core::oPlayer->xBullet[i]->hp = 0;
                Mix_PlayChannel(-1, Core::oSound->attackSound, 0);
            }
        }

        if (xBoss->hp <= 0) {
            Mix_HaltChannel(-1);
            Mix_PlayChannel(-1, Core::oSound->explosionSound, 0);

            Core::enemyWave = Core::fightBoss = 0;

            float _x = xBoss->x + xBoss->srcRect.w / 2;
            float _y = xBoss->y + xBoss->srcRect.h / 2;
            Core::oExplosion->oList.push_back(new Effect(_x, _y, 0, "ExplosionBoss", 1, 9));

            Core::oCoin->Spawn(xBoss->x, xBoss->y, xBoss->srcRect.w, 5, 3);

            delete xBoss;
        }
}

void Bosses::Draw(SDL_Renderer* rR) { xBoss->Draw(rR); }

Boss::Boss(int _type, int _hp):MainObject(0, 0, boss[_type], 2, sheetColumn[_type]) {
        type = _type;
        hp = maxHP = _hp;
        x = 185 + 270 / 2 - srcRect.w / 2;
        y = 10 - 480 - 180;
        moveY = 3;
        d = d2 = 0;
        isReady = 0;
        canShoot = 1;
        hpBar = new MainObject(0, 0, "HealthBar", 3, 1);
}

Boss::~Boss() { }

void Boss::Update() {
        MainObject::Update();
        for (unsigned i = 0; i < bullet.size(); i++) {
            bullet[i]->Update();
            if (Core::oPlayer->hp > 0 && bullet[i]->CollisionWith(Core::oPlayer)) {
                delete bullet[i];
                bullet.erase(bullet.begin() + i);
            }
        }

        if (y >= 10 && !isReady) {
            moveY = 0;
            isReady = 1;
            shootTime = SDL_GetTicks();
        }
        if (isReady && shootTime + 2000 <= SDL_GetTicks()) {
            d = frame = checkPoint = 0;
            space = column;
            if (tag == "Boss01") FPS = 150;
            if (tag == "Boss02") canShoot = 1;
            shootTime = SDL_GetTicks() + 100000;
        }

        if (tag == "Boss00" || tag == "Boss01") {
            if (isReady && space == column && frame == column / 2 && canShoot) {
                d++;
                canShoot = 0;
                Mix_HaltChannel(-1);
                Mix_PlayChannel(-1, Core::oSound->bossAttackSound[rand() % 5], 0);
                if (tag == "Boss00") {
                    bullet.push_back(new BBullet(x + 60, y + 112, "EnemyBullet00", 1, 1, -120, -30));
                    bullet.push_back(new BBullet(x + 60, y + 112, "EnemyBullet00", 1, 1, -10, 0));
                    bullet.push_back(new BBullet(x + 80, y + 112, "EnemyBullet00", 1, 1, 10, 0));
                    bullet.push_back(new BBullet(x + 80, y + 112, "EnemyBullet00", 1, 1, 120, -30));
                } else {
                    bullet.push_back(new BBullet(x + 75, y + 40, "EnemyBullet01", 1, 8, 0, 0));
                }
            }

            if (isReady && space == column && frame == column - 1) canShoot = 1;

            if (isReady && space == column && frame == column - 1)
                if ((tag == "Boss00" && d >= 3) || (tag == "Boss01" && d >= 5)) {
                    space = 0;
                    shootTime = SDL_GetTicks();
                }
        }

        if (tag == "Boss02" && isReady && space == column) {
            if (canShoot) {
                canShoot = 0;
                checkPoint = y - 30;
                moveX = (rand() % 270 + 185 - x - srcRect.w / 2) / 60;
                moveY = -(400 + Core::oPlayer->srcRect.h / 2 - y - srcRect.h / 2) / 60;
            }
            if (y <= checkPoint) {
                checkPoint = -9999;
                Mix_HaltChannel(-1);
                Mix_PlayChannel(-1, Core::oSound->bossAttackSound[rand() % 5], 0);
                moveX = (rand() % 270 + 185 - x - srcRect.w / 2) / 60;
                moveY = (400 + Core::oPlayer->srcRect.h / 2 - y - srcRect.h / 2) / 60;
            }
            if (checkPoint == -9999 && y >= 464 - srcRect.h) {
                moveX = 0;
                moveY = 0;
                checkPoint = -99999;
                shootTime = SDL_GetTicks();
                Mix_HaltChannel(-1);
                Mix_PlayChannel(-1, Core::oSound->bossAttackSound[rand() % 5], 0);
                moveX = (185 + 270 / 2 - srcRect.w / 2 - x) / 30;
                moveY = (10 - y) / 30;
            }
            if (checkPoint == -99999 && y <= 120) {
                shootTime = SDL_GetTicks();
                if (++d2 < 3) {
                    canShoot = 1;
                    shootTime -= 2000;
                } else {
                    canShoot = 0;
                    shootTime += 1000000;
                }
            }
            if (isReady && space == column && checkPoint == -99999 && y <= 10) {
                checkPoint = 0;
                moveX = moveY = 0;
                space = 0;
                d2 = 0;
                shootTime = SDL_GetTicks() + 2000;
                canShoot = 1;
            }
            if (space == column) realRect = {30, 20, 96, 93}; else realRect = {10, 12, 145, 119};
        }
}

void Boss::Draw(SDL_Renderer* rR) {
        MainObject::Draw(rR);
        for (unsigned i = 0; i < bullet.size(); i++) bullet[i]->Draw(rR);

        if (!isReady) return;
        hpBar->x = x + srcRect.w / 2 - hpBar->srcRect.w / 2;
        hpBar->y = y + srcRect.h + 3;
        hpBar->frame = 1;
        hpBar->Update();
        hpBar->Draw(rR);

        int temp = int(float(hp) / float(maxHP) * 49);
        for (int j = 0; j <= temp; j++) {
            hpBar->x = x + srcRect.w / 2 - hpBar->srcRect.w / 2 + 2 + 2 * j;
            hpBar->y = hpBar->y;
            hpBar->frame = 2;
            hpBar->Update();
            hpBar->Draw(rR);
        }
}

BBullet::BBullet(float _x, float _y, string _sprite, int _row, int _column, float desX, float desY):MainObject(_x, _y, _sprite, _row, _column) {
        moveX = (Core::oPlayer->x + Core::oPlayer->srcRect.w / 2 + desX - _x) / 90;
        moveY = (Core::oPlayer->y + Core::oPlayer->srcRect.h / 2 + desY - _y) / 90;
}

BBullet::~BBullet() { }
void BBullet::Update() { MainObject::Update(); }
void BBullet::Draw(SDL_Renderer* rR) { MainObject::Draw(rR); }
