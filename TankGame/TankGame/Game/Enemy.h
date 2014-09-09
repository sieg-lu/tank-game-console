#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "../Base/Global.h"
#include "Tank.h"

class Enemy : public Tank {
public:
    void ai(const Tank &player);
};

#endif ///> end of __ENEMY_H__