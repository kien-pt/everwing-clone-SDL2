#ifndef MAINOBJECT_H
#define MAINOBJECT_H

#include <SDL.h>
#include <vector>
#include <iostream>

using namespace std;

class MainObject {
    public:
        MainObject(float _x, float _y, string _tag, int _row, int _column);
        virtual ~MainObject();

        float x, y;
        SDL_Rect srcRect, realRect;
        int space, frame, column, row;

        unsigned int animTime;
        int FPS;
        SDL_Texture* sprite;

        int hp, maxHP;
        float moveX, moveY;
        string tag;

        virtual void Draw(SDL_Renderer* rR);
        void Update();
        void Destroy(vector <MainObject*> & oVector, int i);
        bool CollisionWith(MainObject* temp);
};

#endif // MAINOBJECT_H
