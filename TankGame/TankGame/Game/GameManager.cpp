#include "stdafx.h"
#include <fstream>
#include <queue>
#include <curses.h>
#include <pthread.h>

#include "Terrain.h"
#include "../Base/ConsoleAPI.h"
#include "GameManager.h"

#define GAME_LOOP_DELAY 50
#define INPUT_DELAY 200

queue<char> gKeysQueue;
pthread_t gKeysThread;
pthread_mutex_t gKeysMutex;

GameManager *GameManager::mInstance = NULL;

GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}

GameManager *GameManager::GetInstance()
{
    if (mInstance == NULL) {
        mInstance = new GameManager();
    }
    return mInstance;
}

void GameManager::DestroyInstance()
{
    if (mInstance != NULL) {
        delete mInstance;
        mInstance = NULL;
    }
}

bool GameManager::Initialize(string filename)
{
    ifstream fin(filename);
    if (!fin) {
        cout << "Open Script File Failed.\n";
        return false;
    }
    fin >> mWidth >> mHeight;

//    mBuffer.resize(mHeight);
    string tmpStr;
    for (int i = 0; i < mHeight; i++) {
        tmpStr.clear();
        tmpStr.resize(mWidth, ' ');
        mBuffer.push_back(tmpStr);
    }

//    cout << mWidth << ' ' << mHeight << endl;
    fin.get();
    string oneLine;
    vector<string> terrain;
    for (int i = 0; i < mHeight; i++) {
        getline(fin, oneLine);
//        cout << oneLine.length() << endl;
        assert(oneLine.length() == mWidth);
        terrain.push_back(oneLine);
    }

    int playerX, playerY;
    fin >> playerX >> playerY;

    bool success = true;
    do {
        Object *tr = new Terrain();
        if (!tr->Initialize((void*)&terrain)) {
            success = false;
            break;
        }
        mObjects.push_back(tr);

        Player *pl = new Player();
        uint arg1 = (playerX & 0x0000ffff);
        uint arg2 = ((playerY & 0x0000ffff) << 16);
        arg1 |= arg2;
        if (!pl->Initialize((void*)(&arg1))) {
            success = false;
            break;
        }
        mPlayer = pl;
        mObjects.push_back((Object*)pl);
    } while (false);

    if (!success) {
        Destroy();
    }

    return true;
}

void *KeyboardInput(void *arg)
{
    char ch;
    while (true) {
        ch = getch();

        pthread_mutex_lock(&gKeysMutex);
        gKeysQueue.push(ch);
        pthread_mutex_unlock(&gKeysMutex);

        if (ch == 27) {
            break;
        }

        Sleep(INPUT_DELAY);
    }
    pthread_exit((void*)0);

    return NULL;
}

bool GameManager::StartGame()
{
    pthread_attr_t attr;
    void *status;

    pthread_mutex_init(&gKeysMutex, NULL);
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&gKeysThread, &attr, KeyboardInput, (void*)0);
    pthread_attr_destroy(&attr);

    while (true) {
        initscr();
        noecho();
        curs_set(FALSE);

        bool bk = true;
        pthread_mutex_lock(&gKeysMutex);
        while (!gKeysQueue.empty()) {
            bk = ProcessKey(gKeysQueue.front());
            gKeysQueue.pop();
            if (!bk) {
                break;
            }
        }
        pthread_mutex_unlock(&gKeysMutex);
        if (!bk) {
            break;
        }

        for (uint i = 0; i < mObjects.size(); i++) {
            mObjects[i]->Render(&mBuffer);
        }

        clear();
        for (int i = 0; i < mHeight; i++) {
            mvprintw(i, 0, mBuffer[i].c_str());
        }
        refresh();
        Sleep(GAME_LOOP_DELAY);
    }
    pthread_join(gKeysThread, &status);
    pthread_mutex_destroy(&gKeysMutex);
    endwin();

    return true;
}

bool GameManager::ProcessKey(int key)
{
    switch (key)
    {
    case 'a': {
//            mBuffer[20][20] = 'X';
        } break;
    case 27: {
            return false;
        } break;
    }

    return true;
}

bool GameManager::Destroy()
{
    for (uint i = 0; i < mObjects.size(); i++) {
        if (mObjects[i] != NULL) {
            mObjects[i]->Destroy();
            delete mObjects[i];
        }
    }
    mObjects.clear();
    DestroyInstance();

    return true;
}
