#ifndef ENEMIES_H
#define ENEMIES_H

#include "MainObject.h"
#include <vector>

using namespace std;

class Enemies
{
    public:
        Enemies();
        virtual ~Enemies();

        void Spawn();
        void Update();
        void SpawnCoin(vector <MainObject*> & oVector, int k, int p);
        void Draw(SDL_Renderer* rR);
        void DrawHealthBar(SDL_Renderer* rR, vector <MainObject*> & oVector, int k);
        void CollisionWithBullet(vector <MainObject*> & oVector, int k);

        vector <MainObject*> list01, list02, list03;
        //vector <MainObject*> list02;
        //vector <MainObject*> zEnemy;
        int mainHP, attaccTime;
    private:
        MainObject* healthBar;
        float theLastEnemyPosition, moveY;
        unsigned  attackTime, waitTime, bonusTime;
};

#endif // ENEMIES_H
