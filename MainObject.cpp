#include "MainObject.h"
#include "Core.h"

MainObject::MainObject(float _x, float _y, string _tag, int _row, int _column) {
        y = _y;
        tag = _tag;

        sprite = Core::oImage->Sprite[tag];
        row = _row;
        column = _column;

        srcRect.x = srcRect.y = 0;
        SDL_QueryTexture(sprite, NULL, NULL, &srcRect.w, &srcRect.h);
        srcRect.w /= column;
        srcRect.h /= row;
        realRect = srcRect;

        FPS = 100;
        space = 0;
        animTime = SDL_GetTicks();

        hp = 9999;
        frame = 0;
        moveX = moveY = 0;

        x = _x - srcRect.w / 2;

        if (tag.substr(0, 10) == "Background") { FPS = 0; moveY = 1; }

        if (tag == "EnemyMain") {
            maxHP = hp = rand() % Core::oEnemies->mainHP + 1;
            moveY = 3;
            realRect = {14, 8, 40, 41};
            space = 6 * (rand() % 5);
        }
        if (tag == "EnemyAttack") {
            moveY = rand() % 3 + 7;
            realRect = {10, 40, 40, 37};
            space = 4 * (rand() % 3);
        }
        if (tag == "EnemyBonus") {
            moveX = -0.5;
            moveY = 0.1;
            hp = maxHP = 100;
            space = 5 * (rand() % 3);
            FPS = 150;
        }

        if (tag == "Boss00") realRect = {26, 44, 104, 101};
        if (tag == "Boss01") realRect = {16, 12, 124, 124};

        if (tag == "Player00") realRect = {6, 14, 20, 34};
        if (tag == "Player01") realRect = {10, 0, 20, 44};
        if (tag == "Player02") realRect = {13, 4, 18, 36};

        if (tag == "Mouse" || tag == "MainMenu") FPS = 0;
        if (tag == "Character" || tag == "Number") FPS = 0;

        if (tag.substr(0, 12) == "PlayerBullet") {
            moveY = -16;
            y -= srcRect.h;
        }
}

MainObject::~MainObject() { }

void MainObject::Draw(SDL_Renderer* rR) {
        SDL_Rect destRect = srcRect;
        destRect.x = int(x);
        destRect.y = int(y);
        SDL_RenderCopyEx(rR, sprite, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void MainObject::Update() {
        srcRect.x = srcRect.w * ((space + frame) % column);
        srcRect.y = srcRect.h * ((space + frame) / column);

        if (FPS != 0 && animTime + FPS <= SDL_GetTicks()) {
            frame = (frame + 1) % column;
            animTime = SDL_GetTicks();
        }

        x += moveX;
        y += moveY;

        if ((tag == "Boss02" || tag.substr(0, 5) == "Enemy") && y <= 465) {
            if (Core::oPlayer->isStar || Core::oPlayer->allKill) return;
            if (Core::oPlayer->starTime + 1000 >= SDL_GetTicks()) return;
            if (CollisionWith(Core::oPlayer)) Core::oPlayer->hp--;
        }
}

bool MainObject::CollisionWith(MainObject* temp) {
        if (temp->x + temp->realRect.x + temp->realRect.w < x + realRect.x || x + realRect.x + realRect.w < temp->x + temp->realRect.x) return 0;
        if (temp->y + temp->realRect.y + temp->realRect.h < y + realRect.y || y + realRect.y + realRect.h < temp->y + temp->realRect.y) return 0;
        return 1;
}

void MainObject::Destroy(vector <MainObject*> & oVector, int i) {
        if (hp <= 0) {
            delete oVector[i];
            oVector.erase(oVector.begin() + i);
        }
}
