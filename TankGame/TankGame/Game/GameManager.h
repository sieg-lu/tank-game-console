#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "../Base/Global.h"
#include "../Base/Object.h"
#include "Player.h"

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
    vector<Object*> mObjects;

    Player *mPlayer;
    bool mIsKeyPressed[256];

    bool ProcessKey(char key);

public:
    bool Initialize(string filename);
    bool StartGame();
    bool Destroy();

};

#endif /// end of __GAME_MANAGER_H__