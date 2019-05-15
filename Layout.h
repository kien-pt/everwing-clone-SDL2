#ifndef LAYOUT_H
#define LAYOUT_H

#include <fstream>
#include "MainObject.h"
#include <vector>

class Layout
{
    public:
        Layout();
        virtual ~Layout();

        void DrawNum(SDL_Renderer* rR, int x, int y, int num, unsigned length);
        void Draw(SDL_Renderer* rR);
    private:
        MainObject* oNum;
        MainObject* character;
        SDL_Rect border1, border2;
};

#endif
