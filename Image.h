#ifndef IMAGE_H
#define IMAGE_H

#include <map>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

class Image
{
    public:
        Image(SDL_Renderer* rR);
        virtual ~Image();

        static map <string, SDL_Texture*> Sprite;
        void loadIMG(SDL_Renderer* rR, string path);
};

#endif
