#pragma once

#include "Game/LiveActor/LiveActor.h"

class CollisionParts;
    
class SeaBottomTriplePropeller : public LiveActor {
public:
    SeaBottomTriplePropeller(const char* pName);
    virtual void init(const JMapInfoIter& rIter);
    virtual void calcAnim();
    virtual void control();

    void exeWait();
    void exeBreak();
    
    CollisionParts* mPropCollision[3];
    // Normally there's an SFX keeper here but uhhhhhhh
};