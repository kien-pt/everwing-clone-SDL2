#include "Layout.h"
#include "Core.h"

Layout::Layout() {
        border1 = {0, 0, 185, 480};
        border2 = {455, 0, 185, 480};
        oNum = new MainObject(0, 2, "Number", 1, 11);
        character = new MainObject(0, 0, "Character", 1, 3);
}

Layout::~Layout() { }

void Layout::DrawNum(SDL_Renderer* rR, int x, int y, int num, unsigned length) {
        unsigned d = 1;
        int temp = num;
        while (temp > 0 || d <= length) {
            oNum->frame = temp % 10;
            temp /= 10;
            oNum->x = x - 16 * (d++) + d;
            oNum->y = y;
            oNum->Update();
            oNum->Draw(rR);
        }
}

void Layout::Draw(SDL_Renderer* rR) {
        if (Core::inGame) {
            oNum->frame = 10;
            oNum->x = 437;
            oNum->y = 2;
            oNum->Update();
            oNum->Draw(rR);
            DrawNum(rR, 437, 2, Core::score, 1);
        }

        if (Core::rankin) {
            ifstream rin("files/ranking.txt");
            for (unsigned i = 0; i < 9; i++) {
                int id, temp;
                rin >> temp >> id;
                DrawNum(rR, 356, 105 + i * 32, temp, 5);
                character->frame = id;
                character->x = 185 + 210;
                character->y = 105 + i * 32;
                character->Update();
                character->Draw(rR);
            }
            rin.close();
        }


        SDL_RenderFillRect(rR, &border1);
        SDL_RenderFillRect(rR, &border2);
}
