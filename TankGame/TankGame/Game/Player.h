#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../Base/Global.h"
#include "Tank.h"

class Player : public Tank {
public:
    virtual bool Render(void *arg);

};

#endif ///> end of __PLAYER_H__