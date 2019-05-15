#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "MainObject.h"
#include <vector>

using namespace std;

class Effect: public MainObject
{
    public:
        Effect(float x, float y, int _space, string _sprite, int _row, int _column);
        virtual ~Effect();

        void Update();
        void Draw(SDL_Renderer* rR);
};

class Explosion
{
    public:
        Explosion();
        virtual ~Explosion();

        void Update();
        void Draw(SDL_Renderer* rR);

        vector <Effect*> oList;
};

#endif
