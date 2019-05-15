#ifndef MAINMENU_H
#define MAINMENU_H

#include "MainObject.h"

class MainMenu: public MainObject
{
    public:
        MainMenu();
        virtual ~MainMenu();

        void Update(SDL_Event* event);
        void Draw(SDL_Renderer* rR);
    private:
        MainObject* num;
        MainObject* tittle[4];
        MainObject* cursor;
        MainObject* character;
        bool canPress;
        int posY, posX, posT;
};

#endif
