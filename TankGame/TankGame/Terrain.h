#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include "Global.h"

class Terrain : public Object {
public:
	// arg is vector<vector<int> > which restore the terrain's info from the script
	virtual bool Initialize(void *arg);
	virtual bool Update();
	virtual bool Render();
	virtual bool Destroy();

private:
	vector<vector<int> > mTerrainInfo;

};

#endif ///> end of __TERRAIN_H__