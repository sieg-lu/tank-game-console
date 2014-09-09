#include "stdafx.h"

#include "../Base/Global.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "Terrain.h"

bool Bullet::Initialize(void *arg)
{
    uint argNum = *(uint*)arg;
    mPosX = (0x0000ffff & argNum);
    mPosY = ((0xffff0000 & argNum) >> 16);
    mIsDead = false;

    return true;
}

bool Bullet::Update(void *arg)
{
    if (mIsDead) {
        return false;
    }
    vector<string>* buffer = (vector<string>*)arg;
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
    if (tmpX >= 0 && tmpX < (*buffer).size() &&
        tmpY >= 0 && tmpY < (*buffer)[0].length()) {
        mPosX = tmpX;
        mPosY = tmpY;
        return true;
    }
    return false;
}

bool Bullet::Render(void *arg)
{
    vector<string>* buffer = (vector<string>*)arg;
    (*buffer)[mPosX][mPosY] = 'O';
    return true;
}

bool Bullet::Destroy()
{
    return true;
}

bool Bullet::Collide(Object *obj)
{
    switch (obj->ThisType())
    {
        case eTerrain:
        {
            Terrain *tr = (Terrain*)obj;
            if (tr->mTerrainInfo[mPosX][mPosY] == '#') {
                mIsDead = true;
            } else if (tr->mTerrainInfo[mPosX][mPosY] == '*') {
                mIsDead = true;
                tr->mTerrainInfo[mPosX][mPosY] = ' ';
            }
        } break;
        case eEnemy:
        {
            Enemy *ene = (Enemy*)obj;
            for (int i = 0; i < 4; i++) {
                int x = ene->mPosX + gTankArea[ene->mDirection][i][0];
                int y = ene->mPosY + gTankArea[ene->mDirection][i][1];
                if (mPosX == x && mPosY == y) {
                    ene->mIsDead = true;
                    mIsDead = true;
                }
            }
        } break;
        case ePlayer:
        {
            Player *pl = (Player*)obj;
            for (int i = 0; i < 4; i++) {
                int x = pl->mPosX + gTankArea[pl->mDirection][i][0];
                int y = pl->mPosY + gTankArea[pl->mDirection][i][1];
                if (mPosX == x && mPosY == y) {
                    pl->mIsDead = true;
                    mIsDead = true;
                }
            }
        }
    }

    return true;
}
