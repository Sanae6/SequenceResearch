#include <math/seadVector.h>
#include <gfx/seadCamera.h>
#include <gfx/seadPrimitiveRenderer.h>
#include <gfx/seadOrthoProjection.h>
#include <gfx/seadViewport.h>
#include "al/util/ControllerUtil.h"
#include "sequences/AmonglaSequence.hpp"
#include "sequences/AmonglaHeaderDump.hpp"
#include "game/HakoniwaSequence/HakoniwaSequence.h"
#include "game/System/Application.h"
#include "logger.hpp"

struct SequenceFactory {
    static al::Sequence* createSequence(const char* name);
};

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
    gLogger->LOG("DRAW MAIN!!!!\n");
    // if (al::isPadHoldA(-1)) {
    //     auto* renderer = sead::PrimitiveRenderer::instance();
    //     renderer->setDrawContext(getDrawInfo()->mDrawContext);
    //     sead::LookAtCamera camera(sead::Vector3f::zero, sead::Vector3f::ez, sead::Vector3f::ey);
    //     sead::OrthoProjection proj;
    //     renderer->setProjection(proj);
    //     renderer->setCamera(camera);
    //     renderer->begin();
    //     renderer->setModelMatrix(sead::Matrix34f::ident);
    //     renderer->end();
    // }
}
