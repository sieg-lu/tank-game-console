#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include "../Base/Global.h"

class Terrain : public Object {
public:
	// arg is vector<vector<char> > which restore the terrain's info from the script
	virtual bool Initialize(void *arg);
	virtual bool Update();
	virtual bool Render(void *arg);
	virtual bool Destroy();

private:
	vector<string> mTerrainInfo;

};

#endif ///> end of __TERRAIN_H__