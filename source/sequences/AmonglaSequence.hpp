#pragma once

#include "al/layout/LayoutActor.h"
#include "al/layout/LayoutKit.h"
#include "al/scene/Scene.h"
#include "al/sequence/Sequence.h"
#include "al/sequence/SequenceInitInfo.h"
#include "al/wipe/WipeHolder.h"

class AmonglaGameDataHolder;
class Gauge;

class AmonglaSequence : public al::Sequence {
public:
    AmonglaSequence(const char* name);
    void init(const al::SequenceInitInfo& initInfo) override;
    void update() override;
    void drawMain() const override;

    void exeLoadScene();
    void exePlay();

    AmonglaGameDataHolder* getGameDataHolder() const { return mGameDataHolder; }

    static const char* name() { return "AmonglaSequence"; }
    static AmonglaSequence* instance();

private:

    al::ScreenCaptureExecutor* mScreenCaptureExecutor;
    AmonglaGameDataHolder* mGameDataHolder;
    al::LayoutActor* mMapPlayer;
    al::LayoutKit* mLayoutKit;
    al::WipeHolder* mWipeHolder;
};
