#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "MainObject.h"

using namespace std;

class Player: public MainObject
{
    public:
        Player(int type);
        virtual ~Player();

        void Input();
        void Update();
        void Draw(SDL_Renderer* rR);

        vector <MainObject*> xBullet;
        bool isStar, isMurshroom, isMagnet, allKill;
        unsigned int starTime, murshroomTime, magnetTime;
    private:
        unsigned int type, shootTime;
};



#endif // PLAYER_H
