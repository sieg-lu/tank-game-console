#include "stdafx.h"

#include "Player.h"


bool Player::Render(void *arg)
{
    if (mIsDead) {
        return false;
    }
    vector<string>* buffer = (vector<string>*)arg;
    for (int i = 0; i < 4; i++) {
        (*buffer)[mPosX + gTankArea[mDirection][i][0]][mPosY + gTankArea[mDirection][i][1]] = gTankArea[mDirection][i][2];
    }

    return true;
}
