#include "stdafx.h"
#include <fstream>
#include <queue>
#include <ctime>
#include <curses.h>
#include <pthread.h>

#include "Terrain.h"
#include "GameManager.h"

#define GAME_LOOP_DELAY 50
#define INPUT_DELAY 200

// queue<char> gKeysQueue;
char gKey;
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
    gKey = 0;
    mIsGameOver = false;
    mRoundCount = 0;
    srand((uint)time(NULL));
//    srand((uint)time(NULL));
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

    bool success = true;
    do {
        Object *tr = new Terrain();
        if (!tr->Initialize((void*)&terrain)) {
            success = false;
            break;
        }
        mObjects.push_back(tr);

        int playerX, playerY;
        fin >> playerX >> playerY;
        uint arg1 = MixInt(playerX, playerY);
        Player *pl = new Player();
        if (!pl->Initialize((void*)(&arg1))) {
            success = false;
            break;
        }
        mPlayer = pl;
        mObjects.push_back((Object*)pl);

        int N, enemyX, enemyY;
        fin >> N;
        bool flag = true;
        while (N-- != 0) {
            fin >> enemyX >> enemyY;
            uint arg1 = MixInt(enemyX, enemyY);
            Object *en = new Enemy();
            if (!en->Initialize((void*)(&arg1))) {
                flag = false;
                break;
            }
            mObjects.push_back(en);
        }
        if (!flag) {
            success = false;
            break;
        }
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
//        gKeysQueue.push(ch);
        gKey = ch;
        if (ch == 27) {
            break;
        }
        pthread_mutex_unlock(&gKeysMutex);
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

        bool win = false;
        if (!mIsGameOver) {
            for (list<Bullet*>::iterator it1 = mBulletsList.begin(); it1 != mBulletsList.end(); it1++) {
                for (list<Object*>::iterator it2 = mObjects.begin(); it2 != mObjects.end(); it2++) {
                    (*it1)->Collide(*it2);
                }
            }
            int enemyCount = 0;
            for (list<Object*>::iterator it = mObjects.begin(); it != mObjects.end(); ) {
                if ((*it)->ThisType() == Object::eEnemy) {
                    Enemy *ene = (Enemy*)(*it);
                    ene->ai(mRoundCount, mPlayer, mBulletsList, mBuffer);
                    enemyCount++;
                }
                if (!(*it)->Update(&mBuffer)) {
//                      list<Object*>::iterator tmpIt = it++;
                    if ((*it) == mPlayer) {
                        mIsGameOver = true;
                    }
                    (*it)->Destroy();
                    delete (*it);
                    mObjects.erase(it++);
                } else {
                    it++;
                }
            }
            if (enemyCount == 0) {
                win = true;
            }
            for (list<Bullet*>::iterator it = mBulletsList.begin(); it != mBulletsList.end(); ) {
                if (!(*it)->Update(&mBuffer)) {
//                      list<Bullet*>::iterator tmpIt = it++;
                    (*it)->Destroy();
                    delete (*it);
                    mBulletsList.erase(it++);
                } else {
                    it++;
                }
            }
//            bool bk = true;
            pthread_mutex_lock(&gKeysMutex);
            if (gKey != 0) {
                ProcessKey(gKey);
                gKey = 0;
            }
//             while (!gKeysQueue.empty()) {
//                 bk = ProcessKey(gKeysQueue.front());
//                 gKeysQueue.pop();
//                 if (!bk) {
//                     break;
//                 }
//             }
//             while (!gKeysQueue.empty()) {
//                 gKeysQueue.pop();
//             }
            pthread_mutex_unlock(&gKeysMutex);

        }
        for (list<Object*>::iterator it = mObjects.begin(); it != mObjects.end(); it++) {
            (*it)->Render(&mBuffer);
        }
        for (list<Bullet*>::iterator it = mBulletsList.begin(); it != mBulletsList.end(); it++) {
            (*it)->Render(&mBuffer);
        }

        clear();
        for (int i = 0; i < mHeight; i++) {
            mvprintw(i, 0, mBuffer[i].c_str());
        }
        mvprintw(mHeight, 0, "Please Don't Hold the Key, Please! *>_<*");

        if (win) {
            mvprintw(2, 2, "You Win!!");
        }
        if (mIsGameOver) {
            mvprintw(2, 2, "Game Over...");
        }

        refresh();
        mRoundCount++;
        if (mRoundCount >= 10000) {
            mRoundCount = 0;
        }
        Sleep(GAME_LOOP_DELAY);
    }
    pthread_join(gKeysThread, &status);
    pthread_mutex_destroy(&gKeysMutex);
    endwin();

    return true;
}

bool GameManager::ProcessKey(char key)
{
    switch (key)
    {
    case 'w': 
        {
            mPlayer->Move(eUp, mBuffer);
        } break;
    case 'a':
        {
            mPlayer->Move(eLeft, mBuffer);
        } break;
    case 's':
        {
            mPlayer->Move(eDown, mBuffer);
        } break;
    case 'd':
        {
            mPlayer->Move(eRight, mBuffer);
        } break;
    case ' ':
        {
            mPlayer->Shoot(mBulletsList, mBuffer);
        } break;
    case 27: 
        {
            exit(0);
        } break;
    }

    return true;
}

bool GameManager::Destroy()
{
    for (list<Object*>::iterator it = mObjects.begin(); it != mObjects.end(); it++) {
        if ((*it) != NULL) {
            (*it)->Destroy();
            delete (*it);
        }
    }
    mObjects.clear();
    DestroyInstance();

    return true;
}
