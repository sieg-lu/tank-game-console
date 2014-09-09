#ifndef __TANK_H__
#define __TANK_H__

#include "../Base/Global.h"

class Tank : public Object {
public:
    // arg => INT, x-pos = LOWER(arg), y-pos = UPPER(arg)
    virtual bool Initialize(void *arg);
    virtual bool Update();
    virtual bool Render(void *arg);
    virtual bool Destroy();

    // Move events should be placed only before rendering parts
    // Return false: Player is dead
    bool Move(eDirection dir, vector<string> &buffer);

    bool IsDead() const { return mIsDead; }

protected:
    eDirection mDirection;
    uint mPosX;
    uint mPosY;

    bool mIsDead;
    // 1: movable
    // 0: not movable
    // -1: dead
    bool Movable(eDirection dir, const vector<string> &buffer, int &newX, int &newY);

};

#endif ///> end of __TANK_H__