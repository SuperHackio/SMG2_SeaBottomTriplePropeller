#include "SeaBottomTriplePropeller.h"

#include "Game/Util.h"

namespace NrvSeaBottomTriplePropeller {
    FULL_NERVE(SeaBottomTriplePropellerNrvBreak, SeaBottomTriplePropeller, Break);
    FULL_NERVE(SeaBottomTriplePropellerNrvWait, SeaBottomTriplePropeller, Wait);
}

SeaBottomTriplePropeller::SeaBottomTriplePropeller(const char* pName) : LiveActor(pName) {
    for (s32 i = 0; i < 3; i++)
        mPropCollision[i] = NULL;
}

void SeaBottomTriplePropeller::init(const JMapInfoIter& rIter) {
    MR::initDefaultPos(this, rIter);

    initModelManagerWithAnm("SeaBottomTriplePropeller", NULL, NULL, false);
    MR::connectToSceneCollisionMapObj(this);
    initHitSensor(1);
    MR::addBodyMessageSensorMapObj(this);
    MR::initCollisionParts(this, "PropellerCap", getSensor("Body"), NULL);
    mPropCollision[0] = MR::createCollisionPartsFromLiveActor(this, "Propeller", getSensor("Body"), MR::getJointMtx(this, "Propeller1"), MR::CollisionScaleType_Default);
    mPropCollision[1] = MR::createCollisionPartsFromLiveActor(this, "Propeller", getSensor("Body"), MR::getJointMtx(this, "Propeller2"), MR::CollisionScaleType_Default);
    mPropCollision[2] = MR::createCollisionPartsFromLiveActor(this, "Propeller", getSensor("Body"), MR::getJointMtx(this, "Propeller3"), MR::CollisionScaleType_Default);
    MR::validateCollisionParts(mPropCollision[0]);
    MR::validateCollisionParts(mPropCollision[1]);
    MR::validateCollisionParts(mPropCollision[2]);
    
    initEffectKeeper(0, NULL, false);

    initSound(4, "SeaBottomTriplePropeller", NULL, NULL);

    MR::setClippingTypeSphereContainsModelBoundingBox(this, 100);

    if (MR::tryRegisterDemoCast(this, rIter))
    {
        MR::registerDemoActionNerve(this, &NrvSeaBottomTriplePropeller::SeaBottomTriplePropellerNrvBreak::sInstance, NULL);
    }

    initNerve(&NrvSeaBottomTriplePropeller::SeaBottomTriplePropellerNrvWait::sInstance, 0);
    makeActorAppeared();
}

void SeaBottomTriplePropeller::control()
{
    //This has the AudSeKeeper in SMG1, but do we really need that here?
}

void SeaBottomTriplePropeller::exeWait()
{
    if (MR::isFirstStep(this))
    {
        MR::startAction(this, "SeaBottomTriplePropeller");
    }

    MR::startLevelSound(this, "SE_OJ_LV_O_TRIPLE_PROP_MOVE", 0, 0, 0);
}

void SeaBottomTriplePropeller::exeBreak() {
    kill();
}

void SeaBottomTriplePropeller::calcAnim()
{
    LiveActor::calcAnim();
    s32 num = 3;
    for (s32 i = 0; i < num; i++)
    {
        mPropCollision[i]->setMtx();
    }
}