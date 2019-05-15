#ifndef SOUND_H
#define SOUND_H
#include <SDL_mixer.h>

class Sound
{
    public:
        Sound();
        virtual ~Sound();

        Mix_Music* bgm;
        Mix_Chunk* mouseSound;
        Mix_Chunk* decideSound;
        Mix_Chunk* attackSound;
        Mix_Chunk* coinSound[5];
        Mix_Chunk* explosionSound;
        Mix_Chunk* bossAttackSound[4];
};

#endif
