#include "stdafx.h"

#include "Tank.h"

bool Tank::Initialize(void *arg)
{
    mDirection = eUp;
    uint argNum = *(uint*)arg;
    mPosX = (0x0000ffff & argNum);
    mPosY = ((0xffff0000 & argNum) >> 16);
    mIsDead = false;

    return true;
}

bool Tank::Update(void *arg)
{
    if (mIsDead) {
        return false;
    }
    return true;
}

// bool Tank::Render(void *arg)
// {
//     if (mIsDead) {
//         return false;
//     }
//     vector<string>* buffer = (vector<string>*)arg;
//     (*buffer)[mPosX][mPosY] = 'X';
//     for (int i = 1; i < 4; i++) {
//         (*buffer)[mPosX + gTankArea[mDirection][i][0]][mPosY + gTankArea[mDirection][i][1]] = gTankArea[mDirection][i][2];
//     }
// 
//     return true;
// }

bool Tank::Destroy()
{
    return true;
}

bool Tank::Movable(eDirection dir, const vector<string> &buffer, int &newX, int &newY)
{
    newX = mPosX, newY = mPosY;
    switch (dir)
    {
        case eUp:
        {
            newX--;
        } break;
        case eLeft:
        {
            newY--;
        } break;
        case eDown:
        {
            newX++;
        } break;
        case eRight:
        {
            newY++;
        } break;
    }

    for (uint i = 0; i < 4; i++) {
        int tmpX = newX + gTankArea[dir][i][0];
        int tmpY = newY + gTankArea[dir][i][1];
        if (tmpX < 0 || tmpX >= buffer.size() ||
            tmpY < 0 || tmpY >= buffer[0].size()) {
            return false;
        }
        if (buffer[tmpX][tmpY] != ' ') {
            return false;
        }
    }
    return true;
}

bool Tank::Move(eDirection dir, vector<string> &buffer)
{
    vector<char> backup;
    for (int i = 0; i < 4; i++) {
        backup.push_back(buffer[mPosX + gTankArea[mDirection][i][0]][mPosY + gTankArea[mDirection][i][1]]);
        buffer[mPosX + gTankArea[mDirection][i][0]][mPosY + gTankArea[mDirection][i][1]] = ' ';
    }
    int newX, newY;
    if (Movable(dir, buffer, newX, newY)) {
        mDirection = dir;
        mPosX = newX;
        mPosY = newY;
        for (int i = 0; i < 4; i++) {
            buffer[mPosX + gTankArea[dir][i][0]][mPosY + gTankArea[dir][i][1]] = gTankArea[dir][i][2];
        }
    } else {
        for (int i = 0; i < 4; i++) {
            buffer[mPosX + gTankArea[mDirection][i][0]][mPosY + gTankArea[mDirection][i][1]] = backup[i];
        }
    }

    return true;
}

bool Tank::Shoot(list<Bullet*> &bulletsList, const vector<string> &buffer)
{
    int tmpX = mPosX;
    int tmpY = mPosY;
    switch (mDirection)
    {
        case eUp:
        {
            tmpX--;
        } break;
        case eLeft:
        {
            tmpY--;
        } break;
        case eDown:
        {
            tmpX++;
        } break;
        case eRight:
        {
            tmpY++;
        } break;
    }
    if (tmpX >= 0 && tmpX < buffer.size() &&
        tmpY >= 0 && tmpY < buffer[0].length()) {
        Bullet *bullet = new Bullet();
        uint arg1 = MixInt(tmpX, tmpY);
        bullet->SetDirection(mDirection);
        if (bullet->Initialize(&arg1)) {
            bulletsList.push_back(bullet);
        } else {
            delete bullet;
        }
        return true;
    }
    return false;
}

