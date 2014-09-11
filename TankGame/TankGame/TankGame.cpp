// TankGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Game/GameManager.h"

int _tmain(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "Usage: TankGame.exe [Level Script Filename]\n";
        system("pause");
        return -1;
    }
    if (GameManager::GetInstance()->Initialize(argv[1])) {
        GameManager::GetInstance()->StartGame();
        GameManager::GetInstance()->Destroy();
    }

//    system("pause");

    return 0;
}

