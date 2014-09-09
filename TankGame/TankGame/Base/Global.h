#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
using namespace std;

#include "Object.h"

typedef unsigned int uint;

enum eDirection {
    eUp = 0,
    eLeft,
    eDown,
    eRight,
};
extern const int gTankArea[4][4][3];

/*
 * #: Wall
 * *: Breakable Wall
 * ^/X: Tank's Head
 * O: Bullet
 */

#endif ///> end of __GLOBAL_H__