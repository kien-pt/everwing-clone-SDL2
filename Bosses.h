#ifndef BOSSES_H
#define BOSSES_H
#include "MainObject.h"
#include <vector>

using namespace std;

class BBullet: public MainObject
{
    public:
        BBullet(float _x, float _y, string _sprite, int _row, int _column, float desX, float desY);
        ~BBullet();

        void Update();
        void Draw(SDL_Renderer* rR);
};

class Boss: public MainObject
{
    public:
        Boss(int _type, int _hp);
        ~Boss();

        bool isReady;
        void Update();
        void Draw(SDL_Renderer* rR);
    private:
        bool canShoot;
        int type, maxHP;
        float checkPoint;
        MainObject* hpBar;
        vector <BBullet*> bullet;
        unsigned shootTime, d, d2;
};

class Bosses
{
    public:
        Bosses();
        virtual ~Bosses();

        void Spawn();
        void Update();
        void Draw(SDL_Renderer* rR);
    private:
        unsigned bossHP, order[3], stt;
        Boss* xBoss;
};

#endif // BOSSES_H
