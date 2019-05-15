#ifndef COIN_H
#define COIN_H

#include "MainObject.h"
#include <vector>

using namespace std;

class Coin
{
    public:
        Coin();
        virtual ~Coin();

        vector <MainObject*> oList;

        void Spawn(float x, float y, int w, int k, int d);
        void Bonus();
        void Update();
        void Draw(SDL_Renderer* rR);
};

#endif
