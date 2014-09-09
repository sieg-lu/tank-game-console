#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include "../Base/Global.h"

class Terrain : public Object {
public:
    // arg is vector<vector<char> > which restore the terrain's info from the script
    virtual bool Initialize(void *arg);
    virtual bool Update(void *arg);
    virtual bool Render(void *arg);
    virtual bool Destroy();

    virtual string Name() { return string("Terrain"); }
    virtual eObjectType ThisType() { return eTerrain; }

    friend class Bullet;

private:
    // mTerrainInfo[x-coordinate][y-coordinate]
    vector<string> mTerrainInfo;
};

#endif ///> end of __TERRAIN_H__