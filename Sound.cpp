#include "Sound.h"
#include "Core.h"

Sound::Sound() {
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

        bgm = Mix_LoadMUS("files/sounds/BGM.mp3");

        coinSound[0] = Mix_LoadWAV("files/sounds/Coin00.wav");
        coinSound[1] = Mix_LoadWAV("files/sounds/Coin01.wav");
        coinSound[2] = Mix_LoadWAV("files/sounds/Coin02.wav");
        coinSound[3] = Mix_LoadWAV("files/sounds/Coin03.wav");
        coinSound[4] = Mix_LoadWAV("files/sounds/Coin04.wav");
        for (int i = 0; i < 5; i++) Mix_VolumeChunk(coinSound[i], 32);

        bossAttackSound[0] = Mix_LoadWAV("files/sounds/BossAttack00.wav");
        bossAttackSound[1] = Mix_LoadWAV("files/sounds/BossAttack01.wav");
        bossAttackSound[2] = Mix_LoadWAV("files/sounds/BossAttack02.wav");
        bossAttackSound[3] = Mix_LoadWAV("files/sounds/BossAttack03.wav");
        bossAttackSound[4] = Mix_LoadWAV("files/sounds/BossAttack04.wav");

        explosionSound = Mix_LoadWAV("files/sounds/Explosion.wav");
        attackSound = Mix_LoadWAV("files/sounds/Attack.wav");
        decideSound = Mix_LoadWAV("files/sounds/Decide.wav");
        mouseSound = Mix_LoadWAV("files/sounds/Cursor.wav");
        Mix_VolumeChunk(attackSound, 32);
}

Sound::~Sound() { }
