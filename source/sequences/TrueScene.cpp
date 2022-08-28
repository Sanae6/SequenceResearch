#include "sequences/TrueScene.hpp"
#include "al/actor/Placement.h"
#include "al/audio/AudioDirector.h"
#include "al/audio/AudioDirectorInitInfo.h"
#include "al/layout/LayoutInitInfo.h"
#include "al/layout/LayoutKit.h"
#include "al/scene/Scene.h"
#include "al/scene/SceneInitInfo.h"
#include "al/util.hpp"
#include "sequences/AmonglaActorFactory.hpp"
#include "sequences/AmonglaGameDataHolder.hpp"
#include "sequences/AmonglaHeaderDump.hpp"
#include "sequences/AmonglaSequence.hpp"

namespace {
    NERVE_DEF(TrueScene, Wait);
}

TrueScene::TrueScene() : al::Scene("TrueScene") {}

void TrueScene::init(const al::SceneInitInfo& initInfo) {
    initNerve(&nrvTrueSceneWait, 0);
    initDrawSystemInfo(initInfo);
    initSceneMsgCtrl();
    initScreenCoverCtrl();
    initSceneStopCtrl();
    initLayoutKit(initInfo);
    getLayoutKit()->createExecuteDirector(0x80);
    initLiveActorKit(initInfo, 0x400, 1, 2);
    // initLiveActorKitWithGraphics(al::GraphicsInitArg(), initInfo, 0x400, 1, 2);
    al::AudioDirectorInitInfo audioInitInfo;
    audioInitInfo.mSequence = NULL;
    audioInitInfo.mCurrentStage = NULL;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x0 = -1;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x4 = -1;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x30 = -1;
    audioInitInfo.unknown_0x20 = 0;
    audioInitInfo.mScenarioNo = 0;
    audioInitInfo.mAudioSystemInfo = NULL;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x8 = 1;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x60 = -1.0;
    audioInitInfo.mSeDirectorInitInfo.mUseMusicEffects = true;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x21 = false;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x28 = NULL;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x58 = 0;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x50 = 0;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x48 = 0;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x40 = 0;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x38 = 0;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x64 = 1.0;
    audioInitInfo.mBgmDirectorInitInfo.unknown_0x0 = false;
    audioInitInfo.mDuckingName = NULL;
    audioInitInfo.mBgmDirectorInitInfo.unknown_0x8 = NULL;
    audioInitInfo.mSeDirectorInitInfo.mName = "注視点";
    audioInitInfo.mSeDirectorInitInfo.unknown_0x18 = 0;
    al::initAudioDirector3D(this, initInfo, audioInitInfo);
    al::initSceneAudioKeeper(this, initInfo, nullptr);
    al::LayoutInitInfo layoutInitInfo;
    al::PlacementInfo placementInfo;
    al::ActorInitInfo actorInitInfo;
    al::initLayoutInitInfo(&layoutInitInfo, this, initInfo);
    al::initActorInitInfo(&actorInitInfo, this, &placementInfo, &layoutInitInfo,
                          new AmonglaActorFactory(), getSceneMsgCtrl(),
                          AmonglaSequence::instance()->getGameDataHolder());

    getLayoutKit()->endInit();
}

void TrueScene::exeWait() {

}