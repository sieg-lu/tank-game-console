#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../Base/Global.h"

class Player : public Object {
public:
    // arg => INT, x-pos = LOWER(arg), y-pos = UPPER(arg)
    virtual bool Initialize(void *arg);
    virtual bool Update();
    virtual bool Render(void *arg);
    virtual bool Destroy();

private:
    eDirection mDirection;
    uint mPosX;
    uint mPosY;

};

#endif ///> end of __PLAYER_H__