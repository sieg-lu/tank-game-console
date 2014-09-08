// TankGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "GameManager.h"

int _tmain(int argc, _TCHAR* argv[])
{
	GameManager::GetInstance()->Initialize("level1.txt");

	system("pause");

	return 0;
}

