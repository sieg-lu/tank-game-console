#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "Global.h"
#include "Object.h"

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
	vector<vector<int> > mBuffer;
	vector<Object*> mObjects;

public:
	bool Initialize(string filename);

};

#endif /// end of __GAME_MANAGER_H__