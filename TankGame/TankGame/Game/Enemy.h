#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "../Base/Global.h"
#include "Tank.h"

class Enemy : public Tank {
public:
    virtual bool Initialize(void *arg);
    virtual bool Render(void *arg);
    void ai(int round, Tank *player, list<Bullet*> &bulletsList, vector<string> &buffer);

    virtual string Name() { return string("Enemy"); }
    virtual eObjectType ThisType() { return eEnemy; }

private:
    eDirection mHoldDirection;

};

#endif ///> end of __ENEMY_H__