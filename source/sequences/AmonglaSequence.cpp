#include <math/seadVector.h>
#include <gfx/seadCamera.h>
#include <gfx/seadPrimitiveRenderer.h>
#include <gfx/seadOrthoProjection.h>
#include <gfx/seadViewport.h>
#include <new>
#include "al/util.hpp"
#include "al/util/ControllerUtil.h"
#include "basis/seadNew.h"
#include "heap/seadHeapMgr.h"
#include "nvn/nvn_api.h"
#include "nvn/nvn_types.h"
#include "sequences/AmonglaSequence.hpp"
#include "sequences/AmonglaHeaderDump.hpp"
#include "game/HakoniwaSequence/HakoniwaSequence.h"
#include "game/System/Application.h"
#include "logger.hpp"
#include "sequences/TrueScene.hpp"

struct SequenceFactory {
    static al::Sequence* createSequence(const char* name);
};

void drawBackground(agl::DrawContext *context);

al::Sequence* amonglaPatch(const char* name) {
    return new AmonglaSequence(AmonglaSequence::name());
}

AmonglaSequence::AmonglaSequence(const char* name) : al::Sequence(name) {
    gLogger->LOG("CONSTRUCTOR\n");
}

void AmonglaSequence::init(const al::SequenceInitInfo &initInfo) {
    gLogger->LOG("INIT\n");
    AmonglaSequence::initDrawSystemInfo(initInfo);
}

void AmonglaSequence::drawMain() const {
    al::Sequence::drawMain();
    gLogger->LOG("AMONGLES\n");

    drawBackground(getDrawInfo()->mDrawContext);
}
