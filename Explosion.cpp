#include "Explosion.h"
#include "Core.h"

Explosion::Explosion() { }

Explosion::~Explosion() { }

void Explosion::Update() {
        for (unsigned int i = 0; i < oList.size(); i++) {
            oList[i]->Update();
            if (oList[i]->hp <= 0) {
                if (oList[i]->tag == "ExplosionBefore" || oList[i]->tag == "ExplosionBonus") {
                    int _x = oList[i]->x + oList[i]->srcRect.w / 2;
                    int _y = oList[i]->y + oList[i]->srcRect.h / 2;
                    oList.push_back(new Effect(_x, _y, 9 * (rand() % 2), "ExplosionAfter", 2, 9));
                }
                delete oList[i];
                oList.erase(oList.begin() + i);
            }
        }
}

void Explosion::Draw(SDL_Renderer* rR) {
        for (unsigned int i = 0; i < oList.size(); i++) oList[i]->Draw(rR);
}

Effect::Effect(float _x, float _y, int _space, string _sprite, int _row, int _column):MainObject(_x, _y, _sprite, _row, _column) {
        x = _x - srcRect.w / 2;
        y = _y - srcRect.h / 2;
        space = _space;
}

Effect::~Effect() { }

void Effect::Update() {
        if (tag != "ExplosionAfter") FPS = 25; else FPS = 75;
        MainObject::Update();
        if (frame == column - 1) hp = 1;
        if (frame == 0 && hp == 1) hp = 0;
        if (hp == 0 && tag == "ExplosionPlayer") Core::rankin = 1;
}

void Effect::Draw(SDL_Renderer* rR) { MainObject::Draw(rR); }

