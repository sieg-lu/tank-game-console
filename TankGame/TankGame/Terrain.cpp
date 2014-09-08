#include "stdafx.h"

#include "Terrain.h"

bool Terrain::Initialize(void *arg)
{
	mTerrainInfo = *(vector<vector<int> >*)(arg);

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

bool Terrain::Render()
{
	return true;
}

bool Terrain::Destroy()
{
	return true;
}
