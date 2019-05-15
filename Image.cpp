#include "Image.h"

map <string, SDL_Texture*> Image::Sprite;

Image::Image(SDL_Renderer* rR) {
        loadIMG(rR, "Background");
        loadIMG(rR, "Background01");
        loadIMG(rR, "Background02");
        loadIMG(rR, "Player00");
        loadIMG(rR, "Player01");
        loadIMG(rR, "Player02");
        loadIMG(rR, "PlayerBullet00");
        loadIMG(rR, "PlayerBullet01");
        loadIMG(rR, "PlayerBullet02");
        loadIMG(rR, "EnemyMain");
        loadIMG(rR, "EnemyAttack");
        loadIMG(rR, "EnemyBonus");
        loadIMG(rR, "ExplosionBefore");
        loadIMG(rR, "ExplosionAfter");
        loadIMG(rR, "ExplosionBoss");
        loadIMG(rR, "ExplosionBonus");
        loadIMG(rR, "ExplosionPlayer");
        loadIMG(rR, "HealthBar");
        loadIMG(rR, "Coin");
        loadIMG(rR, "Boss00");
        loadIMG(rR, "Boss01");
        loadIMG(rR, "Boss02");
        loadIMG(rR, "EnemyBullet00");
        loadIMG(rR, "EnemyBullet01");
        loadIMG(rR, "Number");
        loadIMG(rR, "MainMenu");
        loadIMG(rR, "Mouse");
        loadIMG(rR, "Tittle");
        loadIMG(rR, "Character");
}

Image::~Image() { }

void Image::loadIMG(SDL_Renderer* rR, string path) {
        SDL_Surface* pSurface = IMG_Load(("files/images/" + path + ".png").c_str());
        Uint32 color_key = SDL_MapRGB(pSurface->format, 248, 0, 248);
        SDL_SetColorKey(pSurface, SDL_TRUE, color_key);
        SDL_Texture* finalTexture = SDL_CreateTextureFromSurface(rR, pSurface);
        SDL_FreeSurface(pSurface);
        Sprite[path] = finalTexture;
}
