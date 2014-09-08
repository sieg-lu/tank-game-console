#include "stdafx.h"

#include "Player.h"

bool Player::Initialize(void *arg)
{
    mDirection = eLeft;
    uint argNum = *(uint*)arg;
    mPosX = (0x0000ffff & argNum);
    mPosY = ((0xffff0000 & argNum) >> 16);

    return true;
}

bool Player::Update()
{
    return true;
}

bool Player::Render(void *arg)
{
    vector<string>* buffer = (vector<string>*)arg;
    for (int i = 0; i < 4; i++) {
        (*buffer)[mPosX + gTankArea[mDirection][i][0]][mPosY + gTankArea[mDirection][i][1]] 
            = gTankArea[mDirection][i][2];
    }

    return true;
}

bool Player::Destroy()
{
    return true;
}
