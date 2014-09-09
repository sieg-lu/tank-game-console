#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "../Base/Object.h"
#include "../Base/Global.h"

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"


class GameManager {
private:
    static GameManager *mInstance;
    GameManager();
    ~GameManager();

public:
    static GameManager *GetInstance();
    void DestroyInstance();

private:
    int mHeight;
    int mWidth;
    vector<string> mBuffer;
    list<Object*> mObjects;
    list<Bullet*> mBulletsList;
    bool mIsGameOver;
    int mRoundCount;

    Player *mPlayer;

    bool ProcessKey(char key);

public:
    bool Initialize(string filename);
    bool StartGame();
    bool Destroy();

};

#endif /// end of __GAME_MANAGER_H__