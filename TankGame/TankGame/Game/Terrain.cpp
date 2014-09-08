#include "stdafx.h"

#include "Terrain.h"

bool Terrain::Initialize(void *arg)
{
	mTerrainInfo = *(vector<string>*)(arg);

// 	for (int i = 0; i < mTerrainInfo.size(); i++) {
// 		for (int j = 0; j < mTerrainInfo[i].size(); j++) {
// 			cout << (char)mTerrainInfo[i][j];
// 		}
// 		cout << endl;
// 	}

	return true;
}

bool Terrain::Update()
{
	return true;
}

bool Terrain::Render(void *arg)
{
	vector<string>* buffer = (vector<string>*)arg;
	for (int i = 0; i < mTerrainInfo.size(); i++) {
		for (int j = 0; j < mTerrainInfo[i].size(); j++) {
			(*buffer)[i][j] = mTerrainInfo[i][j];
		}
	}

	return true;
}

bool Terrain::Destroy()
{
	return true;
}
