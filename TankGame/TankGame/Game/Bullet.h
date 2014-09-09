#ifndef __BULLET_H__
#define __BULLET_H__

#include "../Base/Global.h"

class Bullet : public Object {
public:
    virtual bool Initialize(void *arg);
    virtual bool Update(void *arg);
    virtual bool Render(void *arg);
    virtual bool Destroy();

    virtual string Name() { return string("Bullet"); }
    virtual eObjectType ThisType() { return eBullet; }

    bool IsDead() const { return mIsDead; }
    void SetDirection(eDirection val) { mDirection = val; }
    bool Collide(Object *obj);

private:
    eDirection mDirection;
    bool mIsDead;
    int mPosX;
    int mPosY;

};

#endif ///> end of __BULLET_H__