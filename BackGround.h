#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <vector>
#include "MainObject.h"

using namespace std;

class BackGround {
    public:
        BackGround(int type);
        ~BackGround();

        void AddBackground(int pos, int frame, unsigned type);
        void Update();
        void Draw(SDL_Renderer* rR);
    private:
        int type;
        vector <MainObject*> oList;
};

#endif
