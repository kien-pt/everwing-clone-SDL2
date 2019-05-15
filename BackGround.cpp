#include "BackGround.h"
#include "Core.h"

string bg[3] = {"Background", "Background01", "Background02"};

BackGround::BackGround(int _type) {
        type = _type;
        if (type == -1) type = rand() % 3;
        AddBackground(-500, 0, type);
}

BackGround::~BackGround() { }

void BackGround::AddBackground(int pos, int _frame, unsigned type) {
        oList.push_back(new MainObject(185, pos, bg[type], 1, 5));
        oList[oList.size() - 1]->frame = _frame;
}

void BackGround::Update() {
        for (unsigned int i = 0; i < oList.size(); i++) {
            if (oList[i]->y >= 480) oList[i]->hp = 0;
            if (Core::oPlayer->isStar) oList[i]->moveY = 7; else oList[i]->moveY = 1;
            oList[i]->Update();
            oList[i]->Destroy(oList, i);
        }

        int theLastSpritePosition = oList[oList.size() - 1]->y;
        int theLastSpriteFrame = oList[oList.size() - 1]->frame;
        if (theLastSpritePosition >= 0) AddBackground(theLastSpritePosition - 1024, (theLastSpriteFrame + 1) % 5, type);
}

void BackGround::Draw(SDL_Renderer* rR) {
        for (unsigned int i = 0; i < oList.size(); i++) oList[i]->MainObject::Draw(rR);
}
