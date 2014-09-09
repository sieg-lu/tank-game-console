#include "stdafx.h"

#include "Enemy.h"

bool Enemy::Initialize(void *arg)
{
    bool res = Tank::Initialize(arg);
    mDirection = eDown;
    mHoldDirection = eDown;
    return res;
}

bool Enemy::Render(void *arg)
{
    if (mIsDead) {
        return false;
    }
    vector<string>* buffer = (vector<string>*)arg;
    (*buffer)[mPosX][mPosY] = 'X';
    for (int i = 1; i < 4; i++) {
        (*buffer)[mPosX + gTankArea[mDirection][i][0]][mPosY + gTankArea[mDirection][i][1]] = gTankArea[mDirection][i][2];
    }

    return true;
}

void Enemy::ai(int round, Tank *player, list<Bullet*> &bulletsList, vector<string> &buffer)
{
    int interval = (rand() % 8) + 4;
    if ((round % interval) == 0) {
        Shoot(bulletsList, buffer);
        mHoldDirection = (eDirection)(rand() % 4);
    }

//     interval = (rand() % 8) + 4;
//     if ((round % interval) == 0) {
//     }

    if ((round % 3) == 0) {
        Move(mHoldDirection, buffer);
    }
}
