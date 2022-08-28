#include "sequences/AmonglaSequence.hpp"
#include <basis/seadNew.h>
#include <gfx/seadCamera.h>
#include <gfx/seadOrthoProjection.h>
#include <gfx/seadPrimitiveRenderer.h>
#include <gfx/seadViewport.h>
#include <heap/seadHeapMgr.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "AmongWriteStream.hpp"
#include "al/async/AsyncFunctorThread.h"
#include "al/audio/AudioDirectorInitInfo.h"
#include "al/audio/AudioSystemFunction.h"
#include "al/scene/SceneCreator.h"
#include "al/screen/ScreenCaptureExecutor.h"
#include "al/util.hpp"
#include "al/util/ControllerUtil.h"
#include "al/util/MathUtil.h"
#include "al/util/RandomUtil.h"
#include "al/wipe/WipeHolder.h"
#include "al/wipe/WipeSimple.h"
#include "game/GameData/GameDataHolder.h"
#include "game/HakoniwaSequence/HakoniwaSequence.h"
#include "game/StageScene/StageSceneStatePauseMenu.h"
#include "game/System/Application.h"
#include "logger.hpp"
#include "nvn/nvn_api.h"
#include "nvn/nvn_types.h"
#include "sequences/AmonglaGameDataHolder.hpp"
#include "sequences/AmonglaHeaderDump.hpp"
#include "sequences/AmonglaSceneFactory.hpp"
#include "sequences/TrueScene.hpp"

void drawBackground(agl::DrawContext* context);

al::Sequence* amonglaPatch(const char* name) {
    return new AmonglaSequence(AmonglaSequence::name());
}

static AmonglaSequence* sInstance;

AmonglaSequence* AmonglaSequence::instance() {
    return sInstance;
}

namespace {
NERVE_DEF(AmonglaSequence, LoadScene);
NERVE_DEF(AmonglaSequence, Play);
}  // namespace

AmonglaSequence::AmonglaSequence(const char* name) : al::Sequence(name) {
    sInstance = this;
}

void AmonglaSequence::init(const al::SequenceInitInfo& initInfo) {
    AmonglaSequence::initDrawSystemInfo(initInfo);

    mScreenCaptureExecutor = new al::ScreenCaptureExecutor(1);
    const auto physicalArea = getDrawInfo()->mHandheldRenderBuffer->getPhysicalArea();
    mScreenCaptureExecutor->createScreenCapture((int)(physicalArea.getSizeX()),
                                                (int)(physicalArea.getSizeY()), 0);
    sead::Heap* heap = al::getSequenceHeap();

    al::AudioDirectorInitInfo audioInitInfo;
    al::AudioSystemInfo* audioSystemInfo =
        alAudioSystemFunction::getAudioSystemInfo(initInfo.mSystemInfo);
    // todo: clean this up into a default
    audioInitInfo.mSeDirectorInitInfo.unknown_0x0 = -1;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x4 = -1;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x30 = -1;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x60 = -1.0f;
    audioInitInfo.unknown_0x20 = 0;
    audioInitInfo.mScenarioNo = 0;
    audioInitInfo.mAudioSystemInfo = nullptr;
    audioInitInfo.mSequence = 0;
    audioInitInfo.mCurrentStage = nullptr;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x8 = 1;
    audioInitInfo.mSeDirectorInitInfo.mUseMusicEffects = false;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x21 = false;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x28 = nullptr;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x38 = 0;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x64 = 1.0;
    audioInitInfo.mBgmDirectorInitInfo.unknown_0x0 = false;
    audioInitInfo.mSeDirectorInitInfo.mName = "注視点";
    audioInitInfo.mSeDirectorInitInfo.unknown_0x18 = 0;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x50 = 0;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x58 = 0;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x40 = 0;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x48 = 0;
    audioInitInfo.mBgmDirectorInitInfo.unknown_0x8 = nullptr;
    audioInitInfo.mDuckingName = nullptr;

    al::initAudioDirector(this, audioSystemInfo, audioInitInfo);
    initAudioKeeper("Sequence");

    AmonglaGameDataHolder* holder = new AmonglaGameDataHolder(initInfo.mSystemInfo->mMessageSys);
    al::initSceneCreator(this, initInfo, holder, getAudioDirector(), mScreenCaptureExecutor,
                         new AmonglaSceneFactory("アモンガッスのシーン生成"));

    al::ShaderHolder::instance()->initAndLoadAllFromDir("ShaderData", al::getStationedHeap(),
                                                        nullptr);
    // al::AsyncFunctorThread* functor = new al::AsyncFunctorThread("InitSystem", []() {

    // }, 0, 0x20000, sead::CoreId::cSub10);

    mLayoutKit = new al::LayoutKit(initInfo.mSystemInfo->mFontHolder);
    mLayoutKit->setLayoutSystem(initInfo.mSystemInfo->mLayoutSys);
    mLayoutKit->setDrawContext(getDrawInfo()->mDrawContext);
    mLayoutKit->createExecuteDirector(0x80);
    al::LayoutInitInfo layoutInitInfo;
    al::initLayoutInitInfo(&layoutInitInfo, mLayoutKit, nullptr, getAudioDirector(),
                           initInfo.mSystemInfo->mLayoutSys, initInfo.mSystemInfo->mMessageSys,
                           initInfo.mSystemInfo->mGamePadSys);
    mMapPlayer = new al::LayoutActor("チテル");
    al::initLayoutActor(mMapPlayer, layoutInitInfo, "GaugeYoshi", nullptr);
    mMapPlayer->appear();
    al::setPaneLocalScale(mMapPlayer, "All", {5.0f, 5.0f});
    al::startAction(mMapPlayer, "Appear", nullptr);
    mWipeHolder = new al::WipeHolder(1);
    mWipeHolder->registerWipe(
        "FadeWhite", new al::WipeSimple("白フェード", "FadeWhite", layoutInitInfo, nullptr));
    // mWipeHolder->startClose("FadeWhite", 0);

    mLayoutKit->endInit();
    initNerve(&nrvAmonglaSequenceLoadScene, 0);
}
static float actual = 0.5f;

void AmonglaSequence::update() {
    al::Sequence::update();
    al::executeUpdate(mLayoutKit);
    actual += al::isHalfProbability() ? 0.01f : -0.01f;
    actual = al::clamp(actual, 0.0f, 1.0f);
    al::startFreezeAction(mMapPlayer, "Gauge",
                          al::getActionFrameMax(mMapPlayer, "Gauge", "Gauge") * (1.0f - actual),
                          "Gauge");
    // if (mWipeHolder->isCloseEnd()) mWipeHolder->startOpen(500);
    // else if (mWipeHolder->isOpenEnd()) mWipeHolder->startClose("FadeWhite", -1);
}

void AmonglaSequence::drawMain() const {
    al::Sequence::drawMain();

    drawBackground(getDrawInfo()->mDrawContext);
    agl::RenderBuffer* renderBuffer = getDrawInfo()->getRenderBuffer();
    agl::DrawContext* drawContext = getDrawInfo()->mDrawContext;
    mScreenCaptureExecutor->tryCaptureAndDraw(drawContext, renderBuffer, 0);
    sead::Viewport viewport(*renderBuffer);
    viewport.apply(drawContext, *renderBuffer);
    renderBuffer->bind(drawContext);
    al::setRenderBuffer(this->mLayoutKit, renderBuffer);
    al::executeDraw(mLayoutKit, "２Ｄバック（メイン画面）");
    al::executeDraw(mLayoutKit, "２Ｄベース（メイン画面）");
    al::executeDraw(mLayoutKit, "２Ｄオーバー（メイン画面）");
}

void AmonglaSequence::exeLoadScene() {
    // if (al::isFirstStep(this)) {
    //     al::createSceneHeap("TrueScene", false);
    //     sead::ScopedCurrentHeapSetter heapSetter(al::getSceneHeap());
    //     Logger::log("Heap name: %s %x\n", al::getCurrentHeap()->getName().cstr(),
    //                 al::getCurrentHeap()->getFreeSize());
    //     auto* scene = new TrueScene();
    //     al::setSceneAndUseInitThread(this, scene, 0, "WorldMapStage", 1,
    //                                  "Sequence=AmonglaSequence ", nullptr);
    // }

    // if (al::tryEndSceneInitThread(this)) {
    //     al::setNerve(this, &nrvAmonglaSequencePlay);
    // }
}

void AmonglaSequence::exePlay() {}