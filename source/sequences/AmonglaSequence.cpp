#include "sequences/AmonglaSequence.hpp"
#include "game/HakoniwaSequence/HakoniwaSequence.h"
#include "game/System/Application.h"
#include "gfx/seadViewport.h"
#include "logger.hpp"

typedef void (*balls)();



al::Sequence* amonglaPatch(const char* name) {
    // return new HakoniwaSequence(name);
    //gLogger->LOG("we do a little patching\n");
    // return new AmonglaSequence(AmonglaSequence::name);
    // balls ball = nullptr;
    // ball();
    // return nullptr;
}

AmonglaSequence::AmonglaSequence(const char* name) : al::Sequence(name) {
    gLogger->LOG("CONSTRUCTOR\n");
    gLogger->LOG("CONSTRUCTOR\n");
    gLogger->LOG("CONSTRUCTOR\n");
    gLogger->LOG("CONSTRUCTOR\n");
    gLogger->LOG("CONSTRUCTOR\n");
    gLogger->LOG("CONSTRUCTOR\n");
    gLogger->LOG("CONSTRUCTOR\n");
}

void AmonglaSequence::init(const al::SequenceInitInfo &initInfo) {
    gLogger->LOG("INIT\n");
    AmonglaSequence::initDrawSystemInfo(initInfo);
}

void AmonglaSequence::drawMain() {
    al::Sequence::drawMain();
    gLogger->LOG("BALLS\n");
}
