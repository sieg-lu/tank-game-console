#include "stdafx.h"
#include <fstream>

#include "Terrain.h"
#include "GameManager.h"

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
//	cout << mWidth << ' ' << mHeight << endl;
	fin.get();
	string oneLine;
	vector<vector<int> > terrain;
	for (int i = 0; i < mHeight; i++) {
		getline(fin, oneLine);
//		cout << oneLine.length() << endl;
		vector<int> tmp;
		assert(oneLine.length() == mWidth);
		for (int j = 0; j < mWidth; j++) {
			tmp.push_back(oneLine[j]);
		}
		terrain.push_back(tmp);
	}

// 	for (int i = 0; i < mHeight; i++) {
// 		for (int j = 0; j < mWidth; j++) {
// 			cout << (char)terrain[i][j];
// 		}
// 		cout << endl;
// 	}

	bool success = true;
	do {
		Object *tr = new Terrain();
		if (!tr->Initialize((void*)&terrain)) {
			success = false;
			break;
		}
		mObjects.push_back(tr);
	} while (false);

	if (!success) {
		for (int i = 0; i < mObjects.size(); i++) {
			if (mObjects[i] != NULL) {
				mObjects[i]->Destroy();
				delete mObjects[i];
			}
		}
		mObjects.clear();
	}

	return true;
}
