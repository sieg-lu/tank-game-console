#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <iostream>
#include <string>
using namespace std;

class Object {
public:
    virtual bool Initialize(void *arg) = 0;
    virtual bool Update(void *arg) = 0;
    virtual bool Render(void *arg) = 0;
    virtual bool Destroy() = 0;

    enum eObjectType {
        eObject = 0,
        eTank,
        ePlayer,
        eEnemy,
        eBullet,
        eTerrain,
    };
    virtual eObjectType ThisType() { return eObject; }
    virtual string Name() = 0;

};

#endif ///> end of __OBJECT_H__