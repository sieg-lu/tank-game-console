#include "stdafx.h"

#include "Global.h"
#include "Utility.h"

uint MixInt(uint x, uint y)
{
    uint arg1 = (x & 0x0000ffff);
    uint arg2 = ((y & 0x0000ffff) << 16);
    return (arg1 | arg2);
}