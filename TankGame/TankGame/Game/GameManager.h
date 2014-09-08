#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "../Base/Global.h"
#include "../Base/Object.h"

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

	bool ProcessKey(int key);

public:
	bool Initialize(string filename);
	bool StartGame();

};

#endif /// end of __GAME_MANAGER_H__